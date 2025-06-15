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
    namespace core {
        void to_json(nlohmann::json &j, const sf::Vector2f &v);
        void from_json(const nlohmann::json &j, sf::Vector2f &v);
        void to_json(nlohmann::json &j, const sf::Color &c);
        void from_json(const nlohmann::json &j, sf::Color &c);
        void to_json(nlohmann::json &j, const sf::FloatRect &r);
        void from_json(const nlohmann::json &j, sf::FloatRect &r);
    } // core
} // bnjkit
#endif //SFML_JSON_ADAPTER_HPP
