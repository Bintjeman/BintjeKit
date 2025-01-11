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
#include <chrono>
#include "using.hpp"
export module bik.time:clock;
namespace bik::time {
    export using SysClock = std::chrono::steady_clock;
    export using TimePoint = SysClock::time_point;
    export class Clock {
    public:
        Clock();
        ~Clock();
        void start();
        void pause();
        DurationDef restart();
        DurationDef elapsed();

    protected:
        TimePoint start_;
        TimePoint now_;

    private:
        bool paused_;
        TimePoint pause_time_;
    };
}
