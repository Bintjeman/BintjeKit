/*!
 * @author bintjeman
 * @date 04.07.25
 * @name random_engine.cpp
 */
#include "bintjekit/utils/random/random_engine.hpp"
#include <chrono>
namespace bnjkit::utils::random {
    std::mt19937 RandomEngine::s_generator{
        static_cast<unsigned int>(
            std::chrono::system_clock::now().time_since_epoch().count()
        )
    };
    RandomEngine& RandomEngine::instance() {
        static RandomEngine instance;
        return instance;
    }
    void RandomEngine::set_seed(unsigned int seed) {
        s_generator.seed(seed);
    }
    float RandomEngine::get_float(float min, float max) {
        return std::uniform_real_distribution{min, max}(s_generator);
    }
    int RandomEngine::get_int(int min, int max) {
        return std::uniform_int_distribution{min, max}(s_generator);
    }
    double RandomEngine::get_normal(double mean, double stddev) {
        auto& inst = instance();
        inst.m_normal_dist.param(
            std::normal_distribution<>::param_type{mean, stddev}
        );
        return inst.m_normal_dist(s_generator);
    }
    std::mt19937& RandomEngine::getGenerator() {
        return s_generator;
    }
    RandomEngine::RandomEngine() = default;
} // bnjkit::utils::random
