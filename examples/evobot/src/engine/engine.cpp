/*!
 * @author bintjeman
 * @date 23.07.25
 * @name engine.cpp
 */
#include "engine.hpp"

#include <SFML/System/Vector2.hpp>
#include <bintjekit/configuration/json_adapter.hpp>
#include <bintjekit/engine/play_ground.hpp>
#include <bintjekit/engine/gameplay_system_manager.hpp>

#include "common.hpp"
#include "evobot_initialization_system.hpp"
#include "entity/evobot_prefab.hpp"
#include "renderer/renderer.hpp"

namespace evo::engine {
    namespace {
        constexpr sf::Vector2f WORLD_SIZE_DEFAULT{20000, 2000};
        constexpr sf::Vector2f WORLD_POSITION_DEFAULT{- 1.f * WORLD_SIZE_DEFAULT / 2.f};
        constexpr auto EVOBOT_JSPTR = "/Evobot";
        constexpr auto WORLD_SIZE_JSPTR = "/World/Size";
        constexpr auto WORLD_POSITION_JSPTR = "/World/Position";
        constexpr auto WORLD_START_EVOBOTS_JSPTR = "/World/Generation/Start evobots";
        constexpr auto WORLD_MIN_EVOBOTS_JSPTR = "/World/Generation/Min evobots";
        constexpr auto WORLD_MAX_EVOBOTS_JSPTR = "/World/Generation/Max evobots";
        constexpr auto EVOBOT_PREFAB = "evobot";
    }

    Engine::Engine() {
        m_logger->info("Build {}", name());
    }

    Engine::~Engine() {
        m_logger->info("Destroy {}", name());
    }

    void Engine::configure() {
        m_logger->info("Configure {}", name());
        m_custom_settings = m_settings.root().create_child(common::settings_child.evobot);
        m_start_evobots = m_custom_settings.get_or_set(WORLD_START_EVOBOTS_JSPTR, m_start_evobots);
        m_min_evobots = m_custom_settings.get_or_set(WORLD_MIN_EVOBOTS_JSPTR, m_min_evobots);
        m_max_evobots = m_custom_settings.get_or_set(WORLD_MAX_EVOBOTS_JSPTR, m_max_evobots);
        register_prefab(EVOBOT_PREFAB, entity::EvobotPrefab());
        m_logger->debug("make ptr EvobotInitializationSystem");
        auto evobot_settings = m_custom_settings.create_child(EVOBOT_JSPTR);
        auto evobot_initialization_system = std::make_unique<EvobotInitializationSystem>();
        evobot_initialization_system->configuration(evobot_settings);
        m_logger->debug("Engine: add evobot init system to gameplay system manager");
        m_gameplay_system_manager.add_system(std::move(evobot_initialization_system),
                                             bnjkit::engine::GameplayPriority::INPUT
        );
        m_logger->debug("Evo Engine configuration done");
    }
    void Engine::new_world() {
        m_logger->info("New world");
        playground_generation();
        registry().clear();
        for (int i = 0; i < m_start_evobots; ++ i) {
            spawn_prefab(EVOBOT_PREFAB);
        }
        m_state = State::RUNNING;
    }
    void Engine::update() {
        if (m_state != State::CLOSED) {
            m_logger->trace("{}::Update", name());
            m_play_ground->update();
            m_gameplay_system_manager.update(* this);
        }
    }
    std::string Engine::name() const {
        return "Evo Engine";
    }
    void Engine::playground_generation() {
        m_logger->trace("Playground generation");
        m_play_ground->cleanup();
        const sf::Vector2f size = m_custom_settings.get_or_set(WORLD_SIZE_JSPTR, WORLD_SIZE_DEFAULT);
        const sf::Vector2f position = m_custom_settings.get_or_set(WORLD_POSITION_JSPTR, WORLD_POSITION_DEFAULT);
        m_play_ground->set_bounds(position, size);
    }
}
