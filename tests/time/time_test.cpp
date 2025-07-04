/*!
 * @author bintjeman
 * @date 19.06.25
 * @name time_test.cpp
 */
#include <thread>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include "bintjekit/utils/time/time.hpp"

TEST_CASE("Clock functionality", "[time][clock]") {
    bnjkit::utils::time::Clock clock;

    SECTION("Nouvelle horloge démarre proche de zéro") {
        REQUIRE(clock.get() <= 10);
        REQUIRE(clock.get() >= 0);
    }

    SECTION("Reset remet bien à zéro") {
        auto start_time = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto before = clock.get();
        clock.reset();
        auto after = clock.get();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        INFO("Durée totale du test : " << duration.count() << " µs");
        INFO("Valeur de clock après reset : " << after << " ms");
        REQUIRE(after < before);
        REQUIRE(after >= 0);
        const auto TOLERANCE = 10;
        if (after >= TOLERANCE) {
            WARN("Clock.get() >= " << TOLERANCE << ": " << after << " ms (possible surcharge système)");
        }
        REQUIRE(after < TOLERANCE);
    }

    SECTION("Le temps s'écoule") {
        auto start = clock.get();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto end = clock.get();
        REQUIRE(end > start);
    }
}

TEST_CASE("Pulser functionality", "[time][pulser]") {
    bnjkit::utils::time::Pulser pulser;

    SECTION("Fréquence par défaut est 60Hz") {
        REQUIRE(pulser.target_freqency() == 60);
    }

    SECTION("Changement de fréquence") {
        auto freq = GENERATE(1, 30, 60, 120, 1000, take(100,random(1,1000)));
        pulser.set_frequency(freq);
        // WARN("Fréquence demandée : " << freq << ", obtenue : " << pulser.target_freqency());
        REQUIRE(pulser.target_freqency() == freq);
    }

    SECTION("Respect de la fréquence") {
        pulser.set_frequency(10); // 10Hz = période de 100ms
        REQUIRE_FALSE(pulser.pulse()); // Trop tôt
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        REQUIRE(pulser.pulse()); // OK après attente
    }
    SECTION("Précision de la fréquence sur la durée") {
        pulser.set_frequency(60); // 60Hz = période de ~16.67ms
        const int duree_test_secondes = 3;
        const int frequence_attendue = 60;
        int compte_pulses = 0;
        auto debut = std::chrono::steady_clock::now();

        while (std::chrono::duration_cast<std::chrono::seconds>(
                   std::chrono::steady_clock::now() - debut).count() < duree_test_secondes) {
            if (pulser.pulse()) {
                compte_pulses++;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            // petit délai pour ne pas surcharger le CPU
        }

        double frequence_reelle = static_cast<double>(compte_pulses) / duree_test_secondes;
        double marge_erreur = 1.0; // tolérance de ±1Hz

        INFO("Fréquence mesurée : " << frequence_reelle << " Hz");
        REQUIRE(frequence_reelle >= frequence_attendue - marge_erreur);
        REQUIRE(frequence_reelle <= frequence_attendue + marge_erreur);
    }
}

TEST_CASE("Cas particuliers du Pulser", "[time][pulser][edge]") {
    bnjkit::utils::time::Pulser pulser;

        SECTION("Fréquence normale") {
        pulser.set_frequency(60); // 60Hz
        const int duree_test_secondes = 3;
        int compte_pulses = 0;
        auto debut = std::chrono::steady_clock::now();

        while (std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::steady_clock::now() - debut).count() < duree_test_secondes) {
            if (pulser.pulse()) {
                compte_pulses++;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }

        double frequence_reelle = static_cast<double>(compte_pulses) / duree_test_secondes;
        INFO("Fréquence mesurée : " << frequence_reelle << " Hz");
        CHECK(frequence_reelle >= 59.0);
        CHECK(frequence_reelle <= 61.0);
    }

    // Test fréquence nulle (jamais de pulse)
    SECTION("Fréquence nulle") {
        pulser.set_frequency(0);
        for(int i = 0; i < 100; i++) {
            REQUIRE_FALSE(pulser.pulse());
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    // Test fréquence négative (toujours pulse)
    SECTION("Fréquence négative") {
        pulser.set_frequency(-1);
        for(int i = 0; i < 100; i++) {
            REQUIRE(pulser.pulse());
        }
    }
}
