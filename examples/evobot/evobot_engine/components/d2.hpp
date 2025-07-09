/*!
 * @author bintjeman
 * @date 04.07.25
 * @name d2.hpp
 */

#ifndef D2_HPP
#define D2_HPP
#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace evo {
    namespace engine {
        struct D2 {
            using Position = sf::Vector2f;
            using Bounds = sf::Rect<float>;
            Bounds bounds() const;
            Position position;
            float radius;
        };
        struct Movable : public D2 {
            using Velocity = sf::Vector2f;
            Velocity velocity;
            void update();
        };
    } // engine
} // evo

#endif //D2_HPP
