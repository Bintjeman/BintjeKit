/*!
 * @author bintjeman
 * @date 13.07.25
 * @name base_components.hpp
 */

#ifndef EVO_ENGINE_COMP_BASE_COMPONENTS_HPP
#define EVO_ENGINE_COMP_BASE_COMPONENTS_HPP
#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
namespace evo::engine::comp {
    struct D2 {
        sf::Vector2f position{0.f, 0.f};
        float radius{0.f};

        [[nodiscard]] sf::Rect<float> bounds() const {
            return {
                {position.x - radius, position.y - radius},
                {position.x + radius, position.y + radius}
            };
        }
    };

    struct Velocity {
        sf::Vector2f value{0.f, 0.f};
    };

    struct Health {
        float current{100.f};
        float max{100.f};

        void damage(float amount) { current = std::max(0.f, current - amount); }
        void heal(float amount) { current = std::min(max, current + amount); }
    };

    struct Arrow {
        sf::Color color{sf::Color::Yellow};
        float length{30.f};
    };

    // Tags pour identifier les types d'entités
    struct EvobotTag {};
    struct GlobTag {};
}
#endif //EVO_ENGINE_COMP_BASE_COMPONENTS_HPP
