/*!
 * @author bintjeman
 * @date 04.07.25
 * @name d2.hpp
 */
#ifndef BINTJEKIT_D2_HPP
#define BINTJEKIT_D2_HPP
#pragma once
#include <cmath>
#include <SFML/System/Vector2.hpp>
constexpr float PIX2 = 2 * M_PIf;

namespace bnjkit::utils::d2 {
    sf::Vector2f rad_to_vec(float rad);
    float vec_to_rad(sf::Vector2f vec);
}
#endif // BINTJEKIT_D2_HPP
