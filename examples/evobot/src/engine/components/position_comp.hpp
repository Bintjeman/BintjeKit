/*!
 * @author bintjeman
 * @date 23.07.25
 * @name position_comp.hpp
 */
#ifndef EVO_ENGINE_COMPONENTS_POSITION_COMP_HPP
#define EVO_ENGINE_COMPONENTS_POSITION_COMP_HPP
#pragma once
#include <SFML/System/Vector2.hpp>

namespace evo::engine::comp {
    struct PositionComp {
        sf::Vector2f value;
    };
}
#endif
