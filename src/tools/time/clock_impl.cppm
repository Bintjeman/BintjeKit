/*!
 * @file clock_impl.cppm
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
export module bik.time:clock_impl;
import :clock;
namespace bik::time {
    Clock::Clock() {
        start_ = SysClock::now();
        now_ = start_;
    }

    Clock::~Clock() {
    }

    void Clock::start() {
        start_ = SysClock::now();
        now_ = start_;
    }

    void Clock::pause() {
        if (paused_) {
            auto resume_time = SysClock::now();
            start_ += (resume_time - pause_time_);
            paused_ = false;
        } else {
            pause_time_ = SysClock::now();
            paused_ = true;
        }
    }

    DurationDef Clock::restart() {
        DurationDef elapsed_time = elapsed();
        start_ = now_;
        return elapsed_time;
    }

    DurationDef Clock::elapsed() {
        now_ = SysClock::now();
        auto diff = std::chrono::duration_cast<DurationDef>(now_ - start_);
        return diff;
    }
}
