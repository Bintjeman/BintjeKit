/*!
 * @author bintjeman
 * @date 18.06.25
 * @name time.inl.cpp
 */
#ifndef  TIME_INL
#define  TIME_INL
#pragma once
#include "time/time.hpp"
namespace bnjkit::time {
    template<typename Duration>
    Clock<Duration>::Clock() {
        start();
    }
    template<typename Duration>
    Clock<Duration>::~Clock() {
    }

    template<typename Duration>
    void Clock<Duration>::start() {
        _start = clock_type::now();
        _last = _start;
    }

    template<typename Duration>
    void Clock<Duration>::reset() {
        _last = clock_type::now();
    }

    template<typename Duration>
    auto Clock<Duration>::get() const -> long int {
        return std::chrono::duration_cast<Duration>(clock_type::now() - _last).count();
    }

    template<typename Duration>
    auto Clock<Duration>::get_frequency() const -> double {
        return calculate_frequency(get());
    }

    template<typename Duration>
    double Clock<Duration>::calculate_frequency(long int duration) {
        if (duration == 0) {
            return std::numeric_limits<double>::infinity();
        }
        return 1.0 / std::chrono::duration_cast<std::chrono::duration<double> >(Duration(duration)).
               count();
    }

    // Implémentation de Pulser
    template<typename Duration>
    Pulser<Duration>::Pulser() {
        set_frequency(60L);
    }

    template<typename Duration>
    Pulser<Duration>::Pulser(long int frequency) {
        set_frequency(frequency);
    }

    template<typename Duration>
    bool Pulser<Duration>::operator()() {
        return pulse();
    }

    template<typename Duration>
    void Pulser<Duration>::set_frequency(long int pulse_per_second) {
        if (pulse_per_second == 0L) {
            target_interval_ = 0L;
            always_ = false;
            never_ = true;
            target_frequency_ = 0L;
        } else if (pulse_per_second < 0L) {
            target_interval_ = - 1L;
            target_frequency_ = - 1L;
            always_ = true;
            never_ = false;
        } else {
            if (pulse_per_second >= LI_MAXIMUM) {
                target_interval_ = Duration::period::den / LI_MAXIMUM;
                target_frequency_ = LI_MAXIMUM;
            } else {
                target_interval_ = Duration::period::den / pulse_per_second;
                target_frequency_ = pulse_per_second;
            }
            always_ = false;
            never_ = false;
            calc_frequency();
        }
    }

    template<typename Duration>
    void Pulser<Duration>::set_interval(long int pulse_duration) {
        if (pulse_duration <= 0L) {
            target_interval_ = - 1L;
            target_frequency_ = - 1L;
        } else {
            target_interval_ = pulse_duration;
        }
        calc_frequency();
    }

    template<typename Duration>
    bool Pulser<Duration>::pulse() {
        const auto now = Clock<Duration>::clock_type::now();
        const auto elapsed = std::chrono::duration_cast<Duration>(now - this->_last).count();
        if (!never_ && (always_ || elapsed >= target_interval_)) {
            this->_last = now;
            effective_interval_ = elapsed;
            return true;
        }
        return false;
    }

    template<typename Duration>
    long int Pulser<Duration>::effective_interval() const {
        return effective_interval_;
    }

    template<typename Duration>
    long int Pulser<Duration>::effective_frequency() const {
        if (effective_interval_ == 0L) {
            return std::numeric_limits<long int>::max();
        }
        return Duration::period::den / effective_interval_;
    }

    template<typename Duration>
    auto Pulser<Duration>::target_freqency() const -> long int {
        return target_frequency_;
    }

    template<typename Duration>
    void Pulser<Duration>::calc_frequency() {
        if (target_interval_ != 0L) {
            never_ = false;
            if (target_interval_ == - 1L) {
                target_frequency_ = - 1L;
                always_ = true;
            } else {
                target_frequency_ = Duration::period::den / target_interval_;
            }
        } else {
            never_ = true;
            always_ = false;
            target_frequency_ = 0L;
        }
    }
}
#endif // TIME_INL
