/*!
 * @author bintjeman
 * @date 19.06.25
 * @name time_test.cpp
 */
#include <thread>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "time/time.hpp"

TEMPLATE_TEST_CASE("Clock functionality", "[time][clock]",
                   std::chrono::milliseconds, std::chrono::microseconds) {
    bnjkit::time::Clock<TestType> clock;

    SECTION("Nouvelle horloge démarre proche de zéro") {
        REQUIRE(clock.get() <= 1);
    }

    SECTION("Reset remet bien à zéro") {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto before = clock.get();
        clock.reset();
        REQUIRE(clock.get() < before);
        REQUIRE(clock.get() <= 1);
    }

    SECTION("Le temps s'écoule") {
        auto start = clock.get();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto end = clock.get();
        REQUIRE(end > start);
    }
}

TEMPLATE_TEST_CASE("Pulser functionality", "[time][pulser]",
                  std::chrono::milliseconds, std::chrono::microseconds) {
    bnjkit::time::Pulser<TestType> pulser;

    SECTION("Fréquence par défaut est 60Hz") {
        REQUIRE(pulser.target_freqency() == 60);
    }

    SECTION("Changement de fréquence") {
        pulser.set_frequency(30);
        REQUIRE(pulser.target_freqency() == 30);
    }

    SECTION("Premier pulse toujours vrai") {
        REQUIRE(pulser.pulse());
    }

    SECTION("Respect de la fréquence") {
        pulser.set_frequency(10); // 10Hz = période de 100ms
        REQUIRE(pulser.pulse());  // Premier pulse
        REQUIRE_FALSE(pulser.pulse()); // Trop tôt
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        REQUIRE(pulser.pulse());  // OK après attente
    }
}

TEST_CASE("Cas particuliers du Pulser", "[time][pulser][edge]") {
    bnjkit::time::Pulser<std::chrono::milliseconds> pulser;

    SECTION("Fréquence zéro") {
        pulser.set_frequency(0);
        REQUIRE(pulser.pulse()); // Premier pulse OK
        REQUIRE_FALSE(pulser.pulse()); // Ensuite toujours faux
    }

    SECTION("Fréquence très haute") {
        pulser.set_frequency(1000); // 1kHz
        REQUIRE(pulser.pulse());
        std::this_thread::sleep_for(std::chrono::microseconds(900));
        REQUIRE_FALSE(pulser.pulse());
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        REQUIRE(pulser.pulse());
    }
}