/*!
 * @author bintjeman
 * @date 19.07.25
 * @name velocity_compponent.hpp
 */

#ifndef VELOCITY_COMPPONENT_HPP
#define VELOCITY_COMPPONENT_HPP
#pragma once
#include <SFML/System/Vector2.hpp>
namespace bil::components {
    struct VelocityComponent {
        explicit VelocityComponent(const sf::Vector2f& vel = {0.0f, 0.0f}) : velocity(vel) {}
        sf::Vector2f velocity;
    };
}
#endif //VELOCITY_COMPPONENT_HPP
