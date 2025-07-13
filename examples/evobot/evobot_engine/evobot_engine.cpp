/*!
 * @author bintjeman
 * @date 26.06.25
 * @name evobotengine.cpp
 */

#include "evobot_engine.hpp"
#include <spdlog/logger.h>
#include <bintjekit/configuration/sfml_json_adapter.hpp>

#include "evo_world.hpp"

namespace evo::engine {
    EvobotEngine::EvobotEngine() {
        m_logger->info("EvobotEngine: created");
        m_evo_world = std::make_unique<EvoWorld>();
    }
    EvobotEngine::~EvobotEngine() {
        m_logger->info("EvobotEngine: destroyed");
    }
    void EvobotEngine::configure() {
        m_logger->info("EvobotEngine: configuring");
        IEngine::configure();
        m_evo_world->configure(m_settings);
    }
    void EvobotEngine::new_world() {
        m_evo_world = std::make_unique<EvoWorld>();
        m_evo_world->generate();
        m_state = State::READY;
    }
    void EvobotEngine::clear() {
    }
    void EvobotEngine::update() {
        if (m_state == State::READY) {
            m_evo_world->update();
        }
    }
    EvoWorld* EvobotEngine::world() {
        return m_evo_world.get();
    }
    const EvoWorld* EvobotEngine::world() const {
        return m_evo_world.get();
    }

    std::string EvobotEngine::name() const {
        return "EvobotEngine";
    }

    void EvobotEngine::on_sfml_event(const sf::Event& event[[maybe_unused]]) {}
}
