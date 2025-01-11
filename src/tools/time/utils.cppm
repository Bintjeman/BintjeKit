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
export module bik.time:utils;
namespace bik::time {
    // class FrequencyConverter {
    // public:
    template<typename Duration>
    auto to_nanoseconds(const Duration &elapsed_duration) {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_duration).count();
    }

    template<typename Duration>
    auto to_milliseconds(const Duration &elapsed_duration) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_duration).count();
    }

    template<typename Duration>
    auto to_microseconds(const Duration &elapsed_duration) {
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed_duration).count();
    }

    template<typename Duration>
    auto to_seconds(const Duration &elapsed_duration) {
        return std::chrono::duration_cast<std::chrono::seconds>(elapsed_duration).count();
    }

    template<typename Duration>
    auto to_frequency(const Duration &elapsed_duration) {
        if (elapsed_duration.count() == 0) {
            return 0.0;
        }
        auto seconds = std::chrono::duration<double>(elapsed_duration).count();
        return 1.0 / seconds;
    }
    template<typename Precision, typename T>
    auto to_duration(const T frequency) {
        return std::chrono::duration<typename Precision::rep, typename Precision::period>(
            static_cast<typename Precision::rep>(1.0 / static_cast<double>(frequency))
        );
    }

    // };
}
