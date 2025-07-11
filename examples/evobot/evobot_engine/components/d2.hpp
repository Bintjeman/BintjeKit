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

namespace evo::engine {
    struct D2 {
        using Position = sf::Vector2f;
        using Bounds = sf::Rect<float>;
        Bounds bounds() const;
        [[nodiscard]] Position position;
        float radius{0.f};
    };
    struct Movable : D2 {
        using Velocity = sf::Vector2f;
        Velocity velocity;
        void update();
    };
}

#endif //D2_HPP
