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
#include <stdexcept>
#include <chrono>
export module bik.time:pulser_impl;
import :pulser;
import :clock;
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
        if (each_ || this->elapsed() >= interval_) {
            effective_interval_ = this->restart(); // Redémarre l'horloge
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
        auto interval_duration = std::chrono::duration<double>(1.0 / frequency);
        interval_ = std::chrono::duration_cast<Precision>(interval_duration).count();
    }

    template<typename Precision>
    void Pulser<Precision>::set_interval(std::chrono::duration<double> interval) {
        if (interval <= std::chrono::duration<double>(0.0)) {
            each_ = true;
        }
        interval_ = std::chrono::duration_cast<Precision>(interval).count();
    }

    template<typename Precision>
    Precision Pulser<Precision>::interval() const {
        return interval_;
    }

    template<typename Precision>
    Precision Pulser<Precision>::effective_interval() const {
        return effective_interval_;
    }

    template<typename Precision>
    void Pulser<Precision>::each(bool each) {
        each_ = each;
    }
}
