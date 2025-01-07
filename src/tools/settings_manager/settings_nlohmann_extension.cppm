/*!
 * @file settings_nlohmann_extension.cppm
 * @author bintjeman
 * @date 07.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
// ext
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <nlohmann/json.hpp>
export module settings:nlohmann_extension;
export namespace nlohmann {
    template<typename T> struct adl_serializer<sf::Vector2<T> > {
        static void to_json(json& j, const sf::Vector2<T>& v) { j = json{v.x, v.y}; }

        static void from_json(const json& j, sf::Vector2<T>& v) {
            v.x = j.at(0).get<T>();
            v.y = j.at(1).get<T>();
        }
    };
    template<typename T> struct adl_serializer<sf::Rect<T> > {
        static void to_json(json& j, const sf::Rect<T>& r) { j = json{r.left, r.top, r.width, r.height}; }

        static void from_json(const json& j, sf::Rect<T>& r) {
            r.left = j.at(0).get<T>();
            r.top = j.at(1).get<T>();
            r.width = j.at(2).get<T>();
            r.height = j.at(3).get<T>();
        }
    };
    template<> struct adl_serializer<sf::Color> {
        static void to_json(json& j, const sf::Color& c) {
            if (c.a < 255) {
                j = json{c.r, c.g, c.b, c.a};
            } else {
                j = json{c.r, c.g, c.b};
            }
        }
        static void from_json(const json& j, sf::Color& c) {
            c.r = j.at(0).get<std::uint8_t>();
            c.g = j.at(1).get<std::uint8_t>();
            c.b = j.at(2).get<std::uint8_t>();
            // Par défaut, si "a" n'existe pas dans le tableau, il est opaque
            c.a = (j.size() > 3) ? j.at(3).get<std::uint8_t>() : 255;
        }
    };
} // namespace nlohmann

