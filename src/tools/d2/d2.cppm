/*!
 * @file d2.cppm
 * @author bintjeman
 * @date 09.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <algorithm>
#include <SFML/System/Vector2.hpp>
export module bik.d2;
namespace bik::d2 {
    export template<typename T>
    T ratio(T width, T height) { return width / height; }

    export template<typename T>
    T ratio(sf::Vector2<T> size) { return size.x / size.y; }

    export template<typename T>
    T min(sf::Vector2<T> vector) {
        return std::min(vector.x, vector.y);
    }

    export template<typename T>
    T max(sf::Vector2<T> vector) {
        return std::max(vector.x, vector.y);
    }

    export sf::Vector2f upperleft(const sf::Vector2f &position, float radius) {
        return {position.x - radius, position.y - radius};
    }
}
