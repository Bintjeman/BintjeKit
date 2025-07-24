/*!
 * @author bintjeman
 * @date 15.06.25
 * @name sfml_json_adapter.hpp
 *
 * Fichier qui regroupe les methode de serialisation et désérialisation entre
 * nlohmann et d'autres type spécifiques notamment les type sf:: de la sfml
 */

#ifndef BNJKIT_CONFIGURATION_JSON_ADAPTER_HPP
#define BNJKIT_CONFIGURATION_JSON_ADAPTER_HPP
#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "spdlog/spdlog.h"
#include <nlohmann/json.hpp>

namespace nlohmann {
    /*!
     * Convertit un sf::Vector2<T> en object nlohmann::json et inversement.
     *
     * @tparam T int ou float
     */
    template<typename T>
    struct adl_serializer<sf::Vector2<T> > {
        static void to_json(json& j, const sf::Vector2<T>& v) {
            j = json{{"x", v.x}, {"y", v.y}};
        }

        static void from_json(const json& j, sf::Vector2<T>& v) {
            v.x = j.at("x").get<T>();
            v.y = j.at("y").get<T>();
        }
    };
    /*!
     * Convertit un sf::Color en object nlohmann::json et inversement.
     */
    template<>
    struct nlohmann::adl_serializer<sf::Color> {
        static void to_json(nlohmann::json& j, const sf::Color& c) {
            if (c.a == 255) {
                j = nlohmann::json::array({c.r, c.g, c.b});
            } else {
                j = nlohmann::json::array({c.r, c.g, c.b, c.a});
            }
        }

        static void from_json(const nlohmann::json& j, sf::Color& c) {
            if (!j.is_array() || (j.size() != 3 && j.size() != 4)) {
                throw std::invalid_argument("Invalid color format");
            }
            c.r = j.at(0).get<uint8_t>();
            c.g = j.at(1).get<uint8_t>();
            c.b = j.at(2).get<uint8_t>();
            c.a = (j.size() == 4) ? j.at(3).get<uint8_t>() : 255;
        }
    };
    /*!
     * Convertit un sf::Rect<T> en object nlohmann::json et inversement.
     *
     * @tparam T int ou float
     */
    template<typename T>
    struct adl_serializer<sf::Rect<T> > {
        static void to_json(json& j, const sf::Rect<T>& r) {
            j = json{
                {"position", {{"x", r.position.x}, {"y", r.position.y}}},
                {"size", {{"x", r.size.x}, {"y", r.size.y}}}
            };
        }
        static sf::Rect<T> from_json(const json& j) {
            sf::Rect<T> r;
            r.position.x = j["position"]["x"].get<T>();
            r.position.y = j["position"]["y"].get<T>();
            r.size.x = j["size"]["x"].get<T>();
            r.size.y = j["size"]["y"].get<T>();
            return r;
        }
    };
}

/*!
 * Convertit un spdlog::level en object nlohmann::json et inversement.
 */
namespace spdlog::level {
    NLOHMANN_JSON_SERIALIZE_ENUM(spdlog::level::level_enum, {
                                 {spdlog::level::level_enum::trace, "trace"},
                                 {spdlog::level::level_enum::debug, "debug"},
                                 {spdlog::level::level_enum::info, "info"},
                                 {spdlog::level::level_enum::warn, "warn"},
                                 {spdlog::level::level_enum::err, "err"},
                                 {spdlog::level::level_enum::critical, "critical"},
                                 {spdlog::level::level_enum::off, "off"}
                                 })
}
#endif // BNJKIT_CONFIGURATION_JSON_ADAPTER_HPP
