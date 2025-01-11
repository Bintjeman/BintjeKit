/*!
 * @file utils.cppm
 * @author bintjeman
 * @date 11.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <chrono>
#include <type_traits>
#include "using.hpp"
export module bik.time:utils;
namespace bik::time {
    // class Time {
    // public:
    export template<typename T>
    constexpr bool is_chrono_duration_v = false;
    export template<typename Rep, typename Period>
    constexpr bool is_chrono_duration_v<std::chrono::duration<Rep, Period> > = true;

    export template<typename Duration = DurationDef>
    auto to_nanoseconds(const Duration &elapsed_duration) {
        static_assert(is_chrono_duration_v<Duration>, "Duration must be a chrono duration");
        return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_duration).count();
    }

    export template<typename Duration = DurationDef>
    auto to_milliseconds(const Duration &elapsed_duration) {
        static_assert(is_chrono_duration_v<Duration>, "Duration must be a chrono duration");
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_duration).count();
    }

    export template<typename Duration = DurationDef>
    auto to_microseconds(const Duration &elapsed_duration) {
        static_assert(is_chrono_duration_v<Duration>, "Duration must be a chrono duration");
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed_duration).count();
    }

    export template<typename Duration = DurationDef>
    auto to_seconds(const Duration &elapsed_duration) {
        static_assert(is_chrono_duration_v<Duration>, "Duration must be a chrono duration");
        return std::chrono::duration_cast<std::chrono::seconds>(elapsed_duration).count();
    }

    export template<typename Duration = DurationDef, typename T>
    auto to_frequency(T counter, const Duration &elapsed_duration) {
        static_assert(is_chrono_duration_v<Duration>, "Duration must be a chrono duration");
        auto seconds = std::chrono::duration<double>(elapsed_duration);
        if (seconds <= std::chrono::seconds(0)) {
            return std::numeric_limits<double>::infinity();
        }
        return static_cast<double>(static_cast<double>(counter) / seconds.count());
    }

    export template<typename Duration = DurationDef, typename T>
    auto to_duration(const T frequency) -> Duration {
        static_assert(is_chrono_duration_v<Duration>, "Duration must be a chrono duration");
        if (frequency <= 0.0) {
            return Duration::max();
        }
        return Duration(static_cast<typename Duration::rep>(1.0 / static_cast<double>(frequency)));
    }

    // };
}
