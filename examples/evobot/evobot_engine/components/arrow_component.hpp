/*!
 * @author bintjeman
 * @date 10.07.25
 * @name arrow_component.hpp
 */

#ifndef ARROW_COMPONENT_HPP
#define ARROW_COMPONENT_HPP
#pragma once
#include "../../../../include/bintjekit/entity/components/component.hpp"
#include "SFML/Graphics/Color.hpp"

namespace evo::entity {
    class ArrowComponent : public bnjkit::entity::IComponent {
    public:
        explicit ArrowComponent(sf::Color color = sf::Color::Yellow, float length = 30.0f)
            : color(color), length(length) {}

        sf::Color color;
        float length;
    };
}

#endif //ARROW_COMPONENT_HPP
