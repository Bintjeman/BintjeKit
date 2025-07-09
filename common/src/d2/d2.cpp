/*!
 * @author bintjeman
 * @date 04.07.25
 * @name d2.cpp
 */
#include "bintjekit/utils/d2/d2.hpp"
#include <cmath>

namespace bnjkit::utils::d2 {
    sf::Vector2f rad_to_vec(float rad) {
        return {std::cos(rad), std::sin(rad)};
    }
    float vec_to_rad(sf::Vector2f vec) {
        return std::atan2(vec.y, vec.x);
    }
}
