/*!
 * @file clock.cppm
 * @author bintjeman
 * @date 09.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <chrono>>
export module bik.time:clock;
namespace bik::time {
    export using SysClock = std::chrono::steady_clock;
    export using TimePoint = SysClock::time_point;
    // export using Precision = std::chrono::milliseconds;
    export template<typename Precision = std::chrono::nanoseconds>
    class Clock {
    public:
        using Duration = typename Precision::duration;
        Clock();
        ~Clock();
        void start();
        void pause();
        auto restart();
        auto elapsed();

    protected:
        TimePoint start_;
        TimePoint now_;

    private:
        bool paused_;
        TimePoint pause_time_;
    };
}
