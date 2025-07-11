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
        m_start = ClockType::now();
        m_last = m_start;
    }

    void Clock::reset() {
        m_last = ClockType::now();
    }

    auto Clock::get() const -> long int {
        return std::chrono::duration_cast<Duration>(ClockType::now() - m_last).count();
    }

    auto Clock::get_frequency() const -> double {
        return calculate_frequency(get());
    }

    double Clock::calculate_frequency(const long int duration) {
        if (duration == 0) {
            return std::numeric_limits<double>::infinity();
        }
        return 1.0 / std::chrono::duration_cast<std::chrono::duration<double> >(
                   Duration(duration)).
               count();
    }
    Clock::TimePoint Clock::now() {
        return ClockType::now();
    }

    Pulser::Pulser() {
        set_frequency(60L);
    }

    Pulser::Pulser(const long int frequency) {
        set_frequency(frequency);
    }

    bool Pulser::operator()() {
        return pulse();
    }

    void Pulser::set_frequency(const long int pulse_per_second) {
        if (pulse_per_second == 0L) {
            m_target_interval = 0L;
            m_always = false;
            m_never = true;
            m_target_frequency = 0L;
        } else if (pulse_per_second < 0L) {
            m_target_interval = - 1L;
            m_target_frequency = - 1L;
            m_always = true;
            m_never = false;
        } else {
            if (pulse_per_second >= LI_MAXIMUM) {
                m_target_interval = Duration::period::den / LI_MAXIMUM;
                m_target_frequency = LI_MAXIMUM;
            } else {
                m_target_interval = Duration::period::den / pulse_per_second;
                m_target_frequency = pulse_per_second;
            }
            m_always = false;
            m_never = false;
            calc_frequency();
        }
    }

    void Pulser::set_interval(const long int pulse_duration) {
        if (pulse_duration <= 0L) {
            m_target_interval = - 1L;
            m_target_frequency = - 1L;
        } else {
            m_target_interval = pulse_duration;
        }
        calc_frequency();
    }

    bool Pulser::pulse() {
        const auto now = ClockType::now();
        const auto elapsed = std::chrono::duration_cast<Duration>(now - this->m_last).
                count();
        if (!m_never && (m_always || elapsed >= m_target_interval)) {
            this->m_last = now;
            m_effective_interval = elapsed;
            return true;
        }
        return false;
    }

    long int Pulser::effective_interval() const {
        return m_effective_interval;
    }

    long int Pulser::effective_frequency() const {
        if (m_effective_interval == 0L) {
            return std::numeric_limits<long int>::max();
        }
        return Duration::period::den / m_effective_interval;
    }

    auto Pulser::target_freqency() const -> long int {
        return m_target_frequency;
    }

    void Pulser::calc_frequency() {
        if (m_target_interval != 0L) {
            m_never = false;
            if (m_target_interval == - 1L) {
                m_target_frequency = - 1L;
                m_always = true;
            } else {
                m_target_frequency = Duration::period::den / m_target_interval;
            }
        } else {
            m_never = true;
            m_always = false;
            m_target_frequency = 0L;
        }
    }
} // bnjkit::utils::time
