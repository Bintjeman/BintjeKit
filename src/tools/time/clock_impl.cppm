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
export module bik.time:clock_impl;
import :clock;
namespace bik::time {
    template<typename Precision>
    Clock<Precision>::Clock() {
        start_ = SysClock::now();
        now_ = start_;
    }

    template<typename Precision>
    Clock<Precision>::~Clock() {
    }

    template<typename Precision>
    void Clock<Precision>::start() {
        start_ = SysClock::now();
        now_ = start_;
    }

    template<typename Precision>
    void Clock<Precision>::pause() {
        if (paused_) {
            // Si déjà en pause, reprendre le chronométrage
            auto resume_time = SysClock::now();
            start_ += (resume_time - pause_time_); // Ajuste le début pour compenser le temps de pause
            paused_ = false;
        } else {
            // Si actif, mettre en pause
            pause_time_ = SysClock::now();
            paused_ = true;
        }
    }

    template<typename Precision>
    auto Clock<Precision>::restart() {
        auto elapsed_time = elapsed();
        start_ = now_;
        return elapsed_time;
    }

    template<typename Precision>
    auto Clock<Precision>::elapsed() {
        now_ = SysClock::now();
        auto diff = (now_ - start_);
        return diff;
    }
}
