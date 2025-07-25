/*!
 * @author bintjeman
 * @date 23.07.25
 * @name velovity_comp.hpp
 */
#ifndef EVO_ENGINE_COMPONENTS_VELOCITYCOMP_HPP
#define EVO_ENGINE_COMPONENTS_VELOCITYCOMP_HPP
#pragma once
#include <SFML/System/Vector2.hpp>
namespace evo::engine::comp {
    struct VelocityComp {
        sf::Vector2f value;
    };
}
#endif
