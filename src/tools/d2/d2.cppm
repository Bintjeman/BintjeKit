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
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
export module bik.d2;
namespace bik::d2 {
    export
    template<typename T>
    struct circle {
        sf::Vector2<T> position;
        T radius;

        circle(sf::Vector2<T> position, T radius) : position(position), radius(radius) {
        }
    };

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


    export template<typename T>
    sf::Vector2<T> upperleft(const sf::Vector2<T> &position, T radius) {
        return {position.x - radius, position.y - radius};
    }

    export template<typename T>
    bool square_collision(const sf::Rect<float> &a, const sf::Rect<float> &b) {
        // Vérifie si les rectangles se chevauchent
        return (a.position.x < b.position.x + b.size.x &&
                a.position.x + a.size.x > b.position.x &&
                a.position.y < b.position.y + b.size.y &&
                a.position.y + a.size.y > b.position.y);
    }

    export template<typename T>
    bool square_collision(const circle<T> &a, const circle<T> &b) {
        T radius = a.radius + b.radius;
        return (a.position.x - b.position.x < radius &&
                a.position.y - b.position.y < radius);
    }

    export template<typename T>
    T distance_squared(sf::Vector2<T> a, sf::Vector2<T> b) {
        T dist_x = a.x - b.x;
        T dist_y = a.y - b.y;
        return dist_x * dist_x + dist_y * dist_y;
    }

    export template<typename T>
    T distance(sf::Vector2<T> a, sf::Vector2<T> b) {
        return std::sqrt(distance_squared(a, b));
    }
}
