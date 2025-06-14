/*!
 * @author bintjeman
 * @date 14.06.25
 * @name time.hpp
 */

#ifndef TIME_HPP
#define TIME_HPP
#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace bnjkit {
    namespace time {
        static sf::Time frequency_to_time(float frequency = 60.0f);
        static float time_to_frequency(sf::Time time);

        class Pulser {
        public:
            Pulser();
            ~Pulser();
            void start();
            void set_time_per_frame(sf::Time time);
            void set_frequency(float frequency);
            [[nodiscard]] sf::Time time_per_frame() const;
            [[nodiscard]] float frequency() const;
            [[nodiscard]] sf::Time effective_time_per_frame() const;
            [[nodiscard]] float effective_frequency() const;
            bool pulse();

        private:
            sf::Clock m_clock;
            sf::Time m_time_per_frame;
            sf::Time m_effective_time_per_frame;
        };
    } // time
} // bnjkit
#endif //TIME_HPP
