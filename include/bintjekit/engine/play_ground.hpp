/*!
 * @author bintjeman
 * @date 14.06.25
 * @name play_ground.hpp
 */

#ifndef PLAY_GROUND_HPP
#define PLAY_GROUND_HPP
#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"

namespace bnjkit {
    namespace engine {
        struct PlayGround {
        public:
            PlayGround();
            ~PlayGround();
            void update();
            [[nodiscard]] long int ticks() const;
            [[nodiscard]] sf::Rect<float> bounds() const;
            sf::Vector2f size = {0.f, 0.f};
            sf::Vector2f position = {0.f, 0.f};

        private:
            long int ticks_counter = 0;
        };
    } // engine
} // bnjkit

#endif //PLAY_GROUND_HPP
