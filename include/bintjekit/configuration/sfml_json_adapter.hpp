/*!
 * @author bintjeman
 * @date 15.06.25
 * @name sfml_json_adapter.hpp
 */

#ifndef SFML_JSON_ADAPTER_HPP
#define SFML_JSON_ADAPTER_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace bnjkit {
    namespace conf {
        template<typename T>
        void to_json(nlohmann::json &j, const sf::Vector2<T> &v) {
            j = nlohmann::json{{"x", v.x}, {"y", v.y}};
        }
        template<typename T>
        sf::Vector2<T> from_json(const nlohmann::json &j) {
            return {j["x"], j["y"]};
        }
        void to_json(nlohmann::json &j, const sf::Color &c);
        sf::Color from_json(const nlohmann::json &j);
        template<typename T>
        void to_json(nlohmann::json &j, const sf::Rect<T> &r) {
            j = nlohmann::json{
                    {"position", {{"x", r.position.x}, {"y", r.position.y}}},
                    {"size", {{"x", r.size.x}, {"y", r.size.y}}}
            };
        }
        template<typename T>
        sf::Rect<T> from_json(const nlohmann::json &j) {
            sf::Rect<T> r;
            r.position.x = j["position"]["x"].get<T>();
            r.position.y = j["position"]["y"].get<T>();
            r.size.x = j["size"]["x"].get<T>();
            r.size.y = j["size"]["y"].get<T>();
            return r;
        }
    } // core
} // bnjkit
#endif //SFML_JSON_ADAPTER_HPP
