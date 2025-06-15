/*!
 * @author bintjeman
 * @date 15.06.25
 * @name sfml_json_adapter.hpp
 */
#include "bintjekit/configuration/sfml_json_adapter.hpp"

namespace bnjkit {
    namespace conf {
        void to_json(nlohmann::json &j, const sf::Color &c) {
            j = nlohmann::json{{"r", c.r}, {"g", c.g}, {"b", c.b}, {"a", c.a}};
        }

        sf::Color from_json(const nlohmann::json &j) {
            sf::Color c;
            c.r = j.value("r", 255);
            c.g = j.value("g", 255);
            c.b = j.value("b", 255);
            c.a = j.value("a", 255);
            return c;
        }
    } // conf
} // bnjkit
