/*!
 * @author bintjeman
 * @date 04.07.25
 * @name random_engine.cpp
 */
#include "bintjekit/utils/random/random_engine.hpp"
#include <chrono>

namespace bnjkit::utils::random {
    std::mt19937 RandomEngine::m_s_generator{
        static_cast<unsigned int>(
            std::chrono::system_clock::now().time_since_epoch().count()
        )
    };
    RandomEngine& RandomEngine::instance() {
        static RandomEngine instance;
        return instance;
    }
    void RandomEngine::set_seed(const unsigned int seed) {
        m_s_generator.seed(seed);
    }
    bool RandomEngine::get_bool() {
        return std::uniform_int_distribution{0, 1}(m_s_generator) == 1;
    }
    float RandomEngine::get_float(const float min, const float max) {
        return std::uniform_real_distribution{min, max}(m_s_generator);
    }
    int RandomEngine::get_int(const int min, const int max) {
        return std::uniform_int_distribution{min, max}(m_s_generator);
    }
    double RandomEngine::get_normal(const double mean, const double stddev) {
        auto& inst = instance();
        inst.m_normal_dist.param(
            std::normal_distribution<>::param_type{mean, stddev}
        );
        return inst.m_normal_dist(m_s_generator);
    }
    std::mt19937& RandomEngine::get_generator() {
        return m_s_generator;
    }
    RandomEngine::RandomEngine() = default;
} // bnjkit::utils::random
