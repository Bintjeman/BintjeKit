/*!
 * @file pulser_impl.cppm
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
#include <limits>
#include "using.hpp"
export module bik.time:pulser_impl;
import :pulser;
import :clock;
import :utils;
namespace bik::time {
    Pulser::Pulser(): interval_(0) {
        this->start();
    }

    Pulser::~Pulser() {
    }

    bool Pulser::pulse() {
        const auto now = SysClock::now();
        const auto elapsed = now - this->start_;
        if (each_ || elapsed >= interval_) {
            this->start_ = now;
            effective_interval_ = std::chrono::duration_cast<DurationDef>(elapsed);
            return true; // Pulse activée
        }
        return false;
    }

    bool Pulser::operator()() {
        return pulse();
    }

    void Pulser::set_frequency(double frequency) {
        if (frequency <= 0.0) {
            each_ = true;
        }
        interval_ = to_duration<DurationDef>(frequency);
    }

    void Pulser::set_interval(DurationDef interval) {
        if (interval <= DurationDef(0)) {
            each_ = true;
        }
        interval_ = interval;
    }

    auto Pulser::interval() const {
        return interval_;
    }

    auto Pulser::effective_interval() const {
        return effective_interval_;
    }

    auto Pulser::effective_frequency() const {
        if (effective_interval_ == DurationDef(0)) {
            return std::numeric_limits<double>::infinity();
        }
        return to_frequency(effective_interval_);
    }

    void Pulser::each(bool each) {
        each_ = each;
    }
}
