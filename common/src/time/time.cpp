/*!
 * @author bintjeman
 * @date 14.06.25
 * @name time.cpp
 */
#include "time.hpp"

namespace bnjkit {
    namespace time {
        sf::Time frequency_to_time(float frequency) {
            return sf::seconds(1.0f / frequency);
        }

        float time_to_frequency(sf::Time time) {
            return 1.0f / time.asSeconds();
        }

        Pulser::Pulser() {
            set_frequency(60.0f);
            start();
        }

        Pulser::~Pulser() = default;

        void Pulser::start() {
            m_clock.restart();
        }

        void Pulser::set_time_per_frame(sf::Time time) {
            m_time_per_frame = time;
        }

        void Pulser::set_frequency(float frequency) {
            m_time_per_frame = frequency_to_time(frequency);
        }

        sf::Time Pulser::time_per_frame() const {
            return m_time_per_frame;
        }

        float Pulser::frequency() const {
            return time_to_frequency(m_time_per_frame);
        }

        sf::Time Pulser::effective_time_per_frame() const {
            return m_effective_time_per_frame;
        }

        float Pulser::effective_frequency() const {
            return time_to_frequency(m_effective_time_per_frame);
        }

        bool Pulser::pulse() {
            const auto elapsed = m_clock.getElapsedTime();
            if (elapsed >= m_time_per_frame) {
                m_effective_time_per_frame = elapsed;
                m_clock.restart();
                return true;
            }
            return false;
        }

        bool Pulser::operator()() {
            return pulse();
        }
    } // time
} // bnjkit
