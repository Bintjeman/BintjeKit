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
    struct adl_serializer<sf::Color> {
        static void from_json(const json& j, sf::Color& c) {
            c = sf::Color(
                j.at("r").get<uint8_t>(),
                j.at("g").get<uint8_t>(),
                j.at("b").get<uint8_t>(),
                j.contains("a") ? j.at("a").get<uint8_t>() : 255
            );
        }
        static void to_json(json& j, const sf::Color& color) {
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
