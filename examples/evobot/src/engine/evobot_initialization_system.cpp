/*!
 * @author bintjeman
 * @date 23.07.25
 * @name evobot_initialization_system.cpp
 */
#include "evobot_initialization_system.hpp"
#include <bintjekit/utils/random/random_engine.hpp>
#include <bintjekit/engine/i_engine.hpp>
#include <bintjekit/engine/play_ground.hpp>
#include <bintjekit/utils/d2/d2.hpp>

#include "engine.hpp"
#include "components/components.hpp"

namespace evo::engine {
    EvobotInitializationSystem::EvobotInitializationSystem() = default;
    EvobotInitializationSystem::~EvobotInitializationSystem() = default;
    void EvobotInitializationSystem::configuration(bnjkit::conf::Node node) {
        m_logger = bnjkit::logger::Logger::get_logger(bnjkit::literals::logger::ENGINE);
        m_logger->debug("Configuration of {}", name());
        m_min_start_radius = node.get_or_set("/Min start radius", m_min_start_radius);
        m_max_start_radius = node.get_or_set("/Max start radius", m_max_start_radius);
        m_min_start_speed = node.get_or_set("/Min start speed", m_min_start_speed);
        m_max_start_speed = node.get_or_set("/Max start speed", m_max_start_speed);
        m_logger->debug("{} configured", name());
    }
    void EvobotInitializationSystem::update(bnjkit::engine::IEngine& engine) {
        m_logger->info("{}", name());
        auto evobot_engine = dynamic_cast<Engine*>(& engine);
        auto& playground = engine.play_ground();
        auto need_initialization_view = evobot_engine->registry().view<comp::NeedInitializationMark>();
        need_initialization_view.each([this, &evobot_engine, &playground](auto entity) {
            auto& radius_comp = evobot_engine->registry().get<comp::RadiusComp>(entity);
            auto& position_comp = evobot_engine->registry().get<comp::PositionComp>(entity);
            auto& velocity_comp = evobot_engine->registry().get<comp::VelocityComp>(entity);
            radius_comp.value = bnjkit::utils::random::RandomEngine::get_float(m_min_start_radius, m_max_start_radius);
            float x = bnjkit::utils::random::RandomEngine::get_float(playground.position().x,
                                                                     playground.position().x + playground.size().x);
            float y = bnjkit::utils::random::RandomEngine::get_float(playground.position().y,
                                                                     playground.position().y + playground.size().y);
            position_comp.value = {x, y};
            velocity_comp.value = {
                bnjkit::utils::random::RandomEngine::get_float(m_min_start_speed, m_max_start_speed),
                bnjkit::utils::random::RandomEngine::get_float(m_min_start_speed, m_max_start_speed)
            };
            evobot_engine->registry().remove<comp::NeedInitializationMark>(entity);
        });
    }
    std::string EvobotInitializationSystem::name() const {
        return "Evobot Initialization System";
    }
}
