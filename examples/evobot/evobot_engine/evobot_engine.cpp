/*!
 * @author bintjeman
 * @date 26.06.25
 * @name evobotengine.cpp
 */

#include "evobot_engine.hpp"
#include <spdlog/logger.h>
#include <bintjekit/configuration/json_adapter.hpp>

#include "evo_world.hpp"

namespace evo::engine {
    EvobotEngine::EvobotEngine(): IEngine() {
        m_logger->info("EvobotEngine: created");
    }
    EvobotEngine::~EvobotEngine() {
        m_logger->info("EvobotEngine: destroyed");
    }
    void EvobotEngine::initialise() {
        m_logger->info("EvobotEngine: initialise");
        IEngine::initialise();
    }
    void EvobotEngine::configure() {
        m_logger->info("EvobotEngine: configuring");
        IEngine::configure();
    }
    void EvobotEngine::new_world() {}
    std::string EvobotEngine::name() const {
        return "EvobotEngine";
    }
    void EvobotEngine::on_sfml_event(const sf::Event& event[[maybe_unused]]) {}
}
