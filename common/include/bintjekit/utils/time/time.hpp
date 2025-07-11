/*!
 * @author bintjeman
 * @date 14.06.25
 * @name time.hpp
 */
#ifndef BNJTIK_COMMON_TIME_HPP
#define BNJTIK_COMMON_TIME_HPP
#pragma once
#include <chrono>

namespace bnjkit::utils::time {
    static constexpr long int LI_MAXIMUM = std::numeric_limits<long int>::max();
    using Duration = std::chrono::microseconds;
    class Clock {
    public:
        using ClockType = std::chrono::high_resolution_clock;
        using TimePoint = ClockType::time_point;
        Clock();
        ~Clock() = default;
        void start();
        void reset();
        [[nodiscard]] auto get() const -> long int;
        [[nodiscard]] auto get_frequency() const -> double;
        static double calculate_frequency(long int duration);
        static TimePoint now();

    protected:
        TimePoint m_start;
        TimePoint m_last;
    };
    class Pulser : public Clock {
    public:
        Pulser();
        explicit Pulser(long int frequency);
        bool operator()();
        void set_frequency(long int pulse_per_second);
        void set_interval(long int pulse_duration);
        bool pulse();
        [[nodiscard]] long int effective_interval() const;
        [[nodiscard]] long int effective_frequency() const;
        [[nodiscard]] auto target_freqency() const -> long int;

    private:
        void calc_frequency();
        bool m_always{false};
        bool m_never{false};
        long int m_target_frequency{};
        long int m_target_interval{};
        long int m_effective_interval{};
    };
} // bnjkit::utils::time
#endif // BNJTIK_COMMON_TIME_HPP
