/*!
 * @author bintjeman
 * @date 19.06.25
 * @name time.cpp
 */
#include "bintjekit/utils/time/time.hpp"

namespace bnjkit::utils::time {
    Clock::Clock() {
        start();
    }


    void Clock::start() {
        _start = clock_type::now();
        _last = _start;
    }

    void Clock::reset() {
        _last = clock_type::now();
    }

    auto Clock::get() const -> long int {
        return std::chrono::duration_cast<Duration>(clock_type::now() - _last).count();
    }

    auto Clock::get_frequency() const -> double {
        return calculate_frequency(get());
    }

    double Clock::calculate_frequency(long int duration) {
        if (duration == 0) {
            return std::numeric_limits<double>::infinity();
        }
        return 1.0 / std::chrono::duration_cast<std::chrono::duration<double> >(
                   Duration(duration)).
               count();
    }
    Clock::time_point Clock::now() {
        return clock_type::now();
    }

    Pulser::Pulser() {
        set_frequency(60L);
    }

    Pulser::Pulser(long int frequency) {
        set_frequency(frequency);
    }

    bool Pulser::operator()() {
        return pulse();
    }

    void Pulser::set_frequency(long int pulse_per_second) {
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

    void Pulser::set_interval(long int pulse_duration) {
        if (pulse_duration <= 0L) {
            target_interval_ = - 1L;
            target_frequency_ = - 1L;
        } else {
            target_interval_ = pulse_duration;
        }
        calc_frequency();
    }

    bool Pulser::pulse() {
        const auto now = clock_type::now();
        const auto elapsed = std::chrono::duration_cast<Duration>(now - this->_last).
                count();
        if (!never_ && (always_ || elapsed >= target_interval_)) {
            this->_last = now;
            effective_interval_ = elapsed;
            return true;
        }
        return false;
    }

    long int Pulser::effective_interval() const {
        return effective_interval_;
    }

    long int Pulser::effective_frequency() const {
        if (effective_interval_ == 0L) {
            return std::numeric_limits<long int>::max();
        }
        return Duration::period::den / effective_interval_;
    }

    auto Pulser::target_freqency() const -> long int {
        return target_frequency_;
    }

    void Pulser::calc_frequency() {
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
} // bnjkit::utils::time
