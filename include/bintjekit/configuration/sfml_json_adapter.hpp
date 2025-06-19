/*!
 * @author bintjeman
 * @date 15.06.25
 * @name sfml_json_adapter.hpp
 */

#ifndef SFML_JSON_ADAPTER_HPP
#define SFML_JSON_ADAPTER_HPP
#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <nlohmann/json.hpp>
namespace nlohmann {
    template<typename T>
    void to_json(nlohmann::json& j, const sf::Vector2<T>& v) {
        j = nlohmann::json{{"x", v.x}, {"y", v.y}};
    }
    template<typename T>
    sf::Vector2<T> from_json(const nlohmann::json& j) {
        return {j["x"], j["y"]};
    }
    template<>
    struct adl_serializer<sf::Color> {
        static void from_json(const nlohmann::json& j, sf::Color& c) {
            c = sf::Color(
                j.at("r").get<uint8_t>(),
                j.at("g").get<uint8_t>(),
                j.at("b").get<uint8_t>(),
                j.contains("a") ? j.at("a").get<uint8_t>() : 255
            );
        }

        static void to_json(nlohmann::json& j, const sf::Color& color) {
            if (color.a != 255) {
                j = {
                    {"r", color.r},
                    {"g", color.g},
                    {"b", color.b},
                    {"a", color.a}
                };
            } else {
                j = {
                    {"r", color.r},
                    {"g", color.g},
                    {"b", color.b}
                };
            }
        }
    };
    template<typename T>
    void to_json(nlohmann::json& j, const sf::Rect<T>& r) {
        j = nlohmann::json{
            {"position", {{"x", r.position.x}, {"y", r.position.y}}},
            {"size", {{"x", r.size.x}, {"y", r.size.y}}}
        };
    }
    template<typename T>
    sf::Rect<T> from_json(const nlohmann::json& j) {
        sf::Rect<T> r;
        r.position.x = j["position"]["x"].get<T>();
        r.position.y = j["position"]["y"].get<T>();
        r.size.x = j["size"]["x"].get<T>();
        r.size.y = j["size"]["y"].get<T>();
        return r;
    }
}
#endif //SFML_JSON_ADAPTER_HPP
