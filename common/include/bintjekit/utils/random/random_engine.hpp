/*!
 * @author bintjeman
 * @date 04.07.25
 * @name random_engine.hpp
 */
#ifndef BINTJEKIT_COMMON_RANDOM_ENGINE_HPP
#define BINTJEKIT_COMMON_RANDOM_ENGINE_HPP
#pragma once
#include <random>

namespace bnjkit::utils::random {
    class RandomEngine {
    public:
        RandomEngine(const RandomEngine&) = delete;
        RandomEngine& operator=(const RandomEngine&) = delete;

        static void set_seed(unsigned int seed);

        static bool get_bool();
        static float get_float(float min, float max);
        static int get_int(int min, int max);

        static double get_normal(double mean, double stddev);

        static std::mt19937& getGenerator();

    private:
        static RandomEngine& instance();
        RandomEngine();

        static std::mt19937 s_generator;
        std::normal_distribution<> m_normal_dist;
    };
}
#endif //BINTJEKIT_COMMON_RANDOM_ENGINE_HPP
