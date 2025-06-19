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
TEST_CASE("Configuration Manager", "[configuration_manager]") {
    SECTION("Constructor") {
        auto* manager = new bnjkit::conf::Settings();
        REQUIRE(manager);
        delete manager;
    }

}
