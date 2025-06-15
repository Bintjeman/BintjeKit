/*!
 * @author bintjeman
 * @date 15.06.25
 * @name sfml_json_adapter.hpp
 */
#include "bintjekit/configuration/sfml_json_adapter.hpp"

namespace bnjkit::core::conf {
    void to_json(nlohmann::json &j, const sf::Vector2f &v) {
        j = nlohmann::json{{"x", v.x}, {"y", v.y}};
    }

    void from_json(const nlohmann::json &j, sf::Vector2f &v) {
        v.x = j.value("x", 0.0f);
        v.y = j.value("y", 0.0f);
    }

    void to_json(nlohmann::json &j, const sf::Color &c) {
        j = nlohmann::json{{"r", c.r}, {"g", c.g}, {"b", c.b}, {"a", c.a}};
    }

    void from_json(const nlohmann::json &j, sf::Color &c) {
        c.r = j.value("r", 255);
        c.g = j.value("g", 255);
        c.b = j.value("b", 255);
        c.a = j.value("a", 255);
    }

    void to_json(nlohmann::json &j, const sf::FloatRect &r) {
        j = nlohmann::json{
            {"left", r.left}, {"top", r.top},
            {"width", r.width}, {"height", r.height}
        };
    }

    void from_json(const nlohmann::json &j, sf::FloatRect &r) {
        r.left = j.value("left", 0.0f);
        r.top = j.value("top", 0.0f);
        r.width = j.value("width", 0.0f);
        r.height = j.value("height", 0.0f);
    }
}
#endif //SFML_JSON_ADAPTER_HPP
