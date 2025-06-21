/*!
 * @author bintjeman
 * @date 20.06.25
 * @name componants.hpp
 */

#ifndef  TOTO_COMPONENTS_HPP
#define  TOTO_COMPONENTS_HPP
#pragma once
#include <SFML/System/Vector2.hpp>

namespace toto {
    struct Position : sf::Vector2f {
    };
    struct Velocity : sf::Vector2f {
    };
    using Size = float;
    // struct Size : sf::Vector2f {};
    struct D2 {
    public:
        Position position;
        Velocity velocity;
        Size size;
    };
} // toto
#endif // TOTO_COMPONENTS_HPP
