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
    long long Pulser<Precision>::interval() const {
        return interval_;
    }

    template<typename Precision>
    long long Pulser<Precision>::effective_interval() const {
        return effective_interval_;
    }

    template<typename Precision>
    auto Pulser<Precision>::effective_frequency() const -> double {
        // Si l'intervalle effectif est 0, la fréquence ne peut pas être calculée, retourne 0
        if (effective_interval_ == 0) {
            return 0.0;
        }
        // Calcul de la fréquence en fonction de l'intervalle effectif
        auto interval_in_seconds = static_cast<double>(effective_interval_) *
                                   Precision::period::num /
                                   Precision::period::den;

        return 1.0 / interval_in_seconds;
    }

    template<typename Precision>
    void Pulser<Precision>::each(bool each) {
        each_ = each;
    }
}
