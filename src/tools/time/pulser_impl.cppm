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
export module bik.time:pulser_impl;
import :pulser;
import :clock;
import :utils;
namespace bik::time {
    template<typename Precision>
    Pulser<Precision>::Pulser(): interval_(0) {
        this->start();
    }

    template<typename Precision>
    Pulser<Precision>::~Pulser() {
    }

    template<typename Precision>
    bool Pulser<Precision>::pulse() {
        const auto now = SysClock::now();
        const auto elapsed = std::chrono::duration_cast<Precision>(now - this->start_);
        if (each_ || elapsed >= interval_) {
            this->start_ = now;
            effective_interval_ = elapsed;
            return true; // Pulse activée
        }
        return false;
    }

    template<typename Precision>
    bool Pulser<Precision>::operator()() {
        return pulse();
    }

    template<typename Precision>
    void Pulser<Precision>::set_frequency(double frequency) {
        if (frequency <= 0.0) {
            each_ = true;
        }
        interval_ = bik::time::to_duration<Precision>(frequency);
    }

    template<typename Precision>
    void Pulser<Precision>::set_interval(Duration interval) {
        if (interval <= Duration(0.0)) {
            each_ = true;
        }
        interval_ = interval;
    }

    template<typename Precision>
    auto Pulser<Precision>::interval() const {
        return interval_;
    }

    template<typename Precision>
    auto Pulser<Precision>::effective_interval() const {
        return effective_interval_;
    }

    template<typename Precision>
    auto Pulser<Precision>::effective_frequency() const {
        // Si l'intervalle effectif est 0, la fréquence ne peut pas être calculée, retourne 0
        if (effective_interval_ == Duration(0)) {
            return 0.0;
        }
        return to_frequency(effective_interval_);
    }

    template<typename Precision>
    void Pulser<Precision>::each(bool each) {
        each_ = each;
    }
}
