/*!
 * @author bintjeman
 * @date 19.06.25
 * @name configuration_test.cpp
 */
#include <thread>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <bintjekit/configuration/settings.hpp>
#include <bintjekit/configuration/json_adapter.hpp>

#include "bintjekit/configuration/utils.hpp"
#include "SFML/Graphics/Color.hpp"
TEST_CASE("Configuration Manager", "[configuration_manager]") {
    SECTION("Constructor") {
        auto* settings = new bnjkit::conf::Settings();
        REQUIRE(settings);
        delete settings;
    }

    SECTION("Get values") {
        constexpr std::string_view test_string = R"({
    "title": "titre",
    "root": {
        "branch1": {},
        "branch2": {
            "color": {
                "red": 255,
                "green": 100,
                "blue": 50,
                "alpha": 255
            },
            "sf color":{"r":100,"g":150,"b":3}
        },
        "value": 42
    }
})";

        auto settings = bnjkit::conf::Settings();
        settings.load_from_json(bnjkit::conf::from_string(test_string));
        auto red = settings.get<unsigned char>("/root/branch2/color/red"_json_pointer);
        REQUIRE(red == 255);
        auto sf_color = settings.get<sf::Color>("/root/branch2/sf color"_json_pointer);
        REQUIRE(sf_color == sf::Color(100, 150, 3));
    }

    SECTION("Child") {
        constexpr std::string_view test_string = R"({
    "title": "titre",
    "root": {
        "branch1": {},
        "branch2": {
            "color": {
                "red": 255,
                "green": 100,
                "blue": 50,
                "alpha": 255
            },
            "sf color":{"r":100,"g":150,"b":3},
            "value": false
        },
        "value": 42
    }
})";
        auto settings = bnjkit::conf::Settings();
        settings.load_from_json(bnjkit::conf::from_string(test_string));
        auto child = settings.create_child("/root/branch2"_json_pointer);
        auto red = child.get<unsigned char>("/color/red"_json_pointer);
        REQUIRE(red == 255);
        auto sf_color = child.get<sf::Color>("/sf color"_json_pointer);
        REQUIRE(sf_color == sf::Color(100, 150, 3));
        child.set<bool>("/value"_json_pointer, true);
        auto value = settings.get<bool>("/root/branch2/value"_json_pointer);
        REQUIRE(value);
    }
    SECTION("Merge & default") {
        constexpr std::string_view test_string = R"({
    "title": "titre",
    "root": {
        "branch1": {},
        "branch2": {
            "color": {
                "r": 255,
                "g": 100,
                "b": 50,
                "a": 255
            },
            "sf color":{"r":100,"g":150,"b":3},
            "value": false
        },
        "value": 42
    }
})";
        constexpr std::string_view default_str = R"({
    "title": "titre",
    "root": {
        "branch1": {},
        "branch2": {
            "color": {
                "r": 5,
                "g": 5,
                "b": 5
            },
            "color2": {
                "r": 6,
                "g": 7,
                "b": 8,
                "a": 0
            },
            "sf color":{"r":100,"g":150,"b":3},
            "value": false
        },
        "value": 42
    }
})";
        auto settings = bnjkit::conf::Settings();
        settings.load_from_json(bnjkit::conf::from_string(test_string));
        settings.set_default_values(bnjkit::conf::from_string(default_str));
        settings.merge_with_json(bnjkit::conf::from_string(default_str));
        auto color2 = settings.get<sf::Color>("/root/branch2/color2"_json_pointer);
        REQUIRE(color2 == sf::Color(6, 7, 8,0));

        settings.reset_to_defaults();
        auto color = settings.get<sf::Color>("/root/branch2/color"_json_pointer);

        INFO("Couleur reçue : R=" << (int)color.r <<
            ", G=" << (int)color.g <<
            ", B=" << (int)color.b <<
            ", A=" << (int)color.a);
        INFO("Couleur attendue : R=5, G=5, B=5, A=255");

        REQUIRE(color == sf::Color(5, 5, 5));
    }
}
