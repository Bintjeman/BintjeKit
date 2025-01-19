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
#include <tools/logger/logger_define.hpp>
export module bik.time:pulser_impl;
import :pulser;
import :clock;
import :utils;
import bik.logger;
namespace bik::time {
    Pulser::Pulser(): interval_(0) {
        this->start();
    }

    Pulser::~Pulser() =default;
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
    LOGGER->trace("set_frequency(): Set frequency to {}", frequency);
        if (frequency <= 0.0) {
            each_ = true;
        }
        interval_ = to_duration<DurationDef>(frequency);
        LOGGER->trace("Set interval milli to {}", to_milliseconds(interval_));
        LOGGER->trace("with frequency {}", frequency);
    }

    void Pulser::set_interval(DurationDef interval) {
        LOGGER->trace("set_interval(): Set interval to {}", interval.count());
        if (interval <= DurationDef(0)) {
            each_ = true;
        }
        interval_ = interval;
        LOGGER->trace("Set interval to {}", interval_.count());
        LOGGER->trace("with frequency {}", to_frequency(1, interval_));
    }

    auto Pulser::interval() const {
        return interval_;
    }
    auto Pulser::frequency() const {
        return to_frequency(1, interval_);
    }

    auto Pulser::effective_interval() const {
        return effective_interval_;
    }

    auto Pulser::effective_frequency() const {
        if (effective_interval_ == DurationDef(0)) {
            return std::numeric_limits<double>::infinity();
        }
        return to_frequency(1, effective_interval_);
    }

    void Pulser::each(bool each) {
        each_ = each;
    }
}
