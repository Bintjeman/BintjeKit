/*!
 * @author bintjeman
 * @date 23.07.25
 * @name evobot_initialization_system.hpp
 */
#ifndef EVOBOT_INITIALIZATION_SYSTEM_HPP
#define EVOBOT_INITIALIZATION_SYSTEM_HPP
#pragma once
#include <spdlog/fwd.h>
#include <bintjekit/ecs/system/i_system.hpp>
#include "application.hpp"
namespace bnjkit::conf {
    class Node;
}

namespace evo::engine {
    class EvobotInitializationSystem final : public bnjkit::ecs::ISystem {
    public:
        EvobotInitializationSystem();
        ~EvobotInitializationSystem() override;
        void configuration(bnjkit::conf::Node node);
        void update(bnjkit::engine::IEngine& engine) override;
        [[nodiscard]] std::string name() const override;

    private:
        float m_min_start_radius{1.f};
        float m_max_start_radius{10.f};
        float m_min_start_speed{1.f};
        float m_max_start_speed{1.f};
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#endif
