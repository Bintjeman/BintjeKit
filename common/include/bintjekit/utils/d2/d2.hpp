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
namespace bnjkit::utils::d2 {
    constexpr float PIX2 = 2 * M_PIf;
    sf::Vector2f rad_to_vec(float rad);
    float vec_to_rad(sf::Vector2f vec);
    template<typename T>
    T min_sf(const sf::Vector2<T>& vec) {
        return std::min(vec.x, vec.y);
    }
    template<typename T>
    T max_sf(const sf::Vector2<T>& vec) {
        return std::max(vec.x, vec.y);
    }
}
#endif // BINTJEKIT_D2_HPP
