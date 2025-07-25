/*!
 * @author bintjeman
 * @date 23.07.25
 * @name engine.hpp
 */
#ifndef EVOBOT_ENGINE_ENGINE_HPP
#define EVOBOT_ENGINE_ENGINE_HPP
#pragma once
#include <bintjekit/engine/i_engine.hpp>

namespace evo::engine {
    class Engine final : public bnjkit::engine::IEngine {
    public:
        Engine();
        ~Engine() override;
        void configure() override;
        void new_world();
        void update() override;
        [[nodiscard]] std::string name() const override;

    private:
        void playground_generation();
        int m_start_evobots{10};
        int m_min_evobots{1};
        int m_max_evobots{100};
    };
}
#endif
