/*!
 * @author bintjeman
 * @date 19.07.25
 * @name position_component.hpp
 */

#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP
#pragma once
#include <SFML/System/Vector2.hpp>
namespace bil::components {
    struct PositionComponent {
        explicit PositionComponent(const sf::Vector2f& pos = {0.0f, 0.0f}) : position(pos) {}
        sf::Vector2f position;
    };
}
#endif //POSITION_COMPONENT_HPP
