/*!
 * @author bintjeman
 * @date 26.06.25
 * @name evobotengine.cpp
 */

#include "evobot_engine.hpp"
#include <spdlog/logger.h>
#include <SFML/System/Vector2.hpp>
#include <bintjekit/utils/random/random_engine.hpp>
#include <bintjekit/utils/d2/d2.hpp>
#include <bintjekit/configuration/sfml_json_adapter.hpp>
#include "evobot_engine/entity.hpp"
#include "evobot_engine/evobot.hpp"
#include "evobot_engine/glob.hpp"
#include "evobot_engine/components/d2.hpp"

namespace evo::engine {
    EvobotEngine::EvobotEngine() {
        m_logger->info("EvobotEngine: created");
        entity_manager().create_collection<engine::Evobot>();
        entity_manager().create_collection<engine::Glob>();
    }

    EvobotEngine::~EvobotEngine() {
        m_logger->info("EvobotEngine: destroyed");
    }

    void EvobotEngine::configure() {
        m_logger->info("EvobotEngine: configuring");
        IEngine::configure();
        m_minimum_bot = m_custom_settings.get_or_set("/Rules/Minimum bot", 0u);
        m_maximum_bot = m_custom_settings.get_or_set("/Rules/Maximum bot", 10u);
        m_bot_min_radius = m_custom_settings.get_or_set("/Rules/Bot/Min radius", 1.f);
        m_bot_max_radius = m_custom_settings.get_or_set("/Rules/Bot/Max radius", 10.f);
        m_bot_max_speed = m_custom_settings.get_or_set("/Rules/Bot/Max speed", 10.f);
        m_minimum_glob = m_custom_settings.get_or_set("/Rules/Minimum glob", 0u);
        m_maximum_glob = m_custom_settings.get_or_set("/Rules/Maximum glob", 10u);
        m_glob_min_radius = m_custom_settings.get_or_set("/Rules/Glob/Min radius", 1.f);
        m_glob_max_radius = m_custom_settings.get_or_set("/Rules/Glob/Max radius", 10.f);
        m_glob_max_speed = m_custom_settings.get_or_set("/Rules/Glob/Max speed", 10.f);
    }

    void EvobotEngine::new_world() {
        m_logger->info("EvobotEngine: new world");
        m_entity_manager->clear();
        // Configuration
        unsigned int start_bot = m_custom_settings.
                get_or_set("/Rules/Generation/Start bot", 100u);
        unsigned int start_glob = m_custom_settings.get_or_set(
            "/Rules/Generation/Start glob", 100u);
        // Playground
        {
            bnjkit::engine::PlayGround new_playground;
            sf::Vector2f size = m_custom_settings.get_or_set(
                "/Playground/Size",
                sf::Vector2f{1'000.f, 1'000.f}
            );
            sf::Vector2f playground_position = m_custom_settings.get_or_set(
                "/Playground/Position",
                sf::Vector2f{0.f, 0.f}
            );
            new_playground.size = size;
            new_playground.position = playground_position;
            m_play_ground = std::make_unique<bnjkit::engine::PlayGround>(new_playground);
        }
        // Evobots
        for (unsigned int i = 0; i < start_bot; ++ i) {
            auto evobot = m_entity_manager->create<Evobot>();
            float radius = bnjkit::utils::random::RandomEngine::get_float(
                m_bot_min_radius,
                m_bot_max_radius
            );
            evobot->set_radius(radius);
            D2::Position position;
            position.x = bnjkit::utils::random::RandomEngine::get_float(
                0.f,
                m_play_ground->size.x
            );
            position.y = bnjkit::utils::random::RandomEngine::get_float(
                0.f,
                m_play_ground->size.y
            );
            evobot->set_position(position);
            float angle_rnd = bnjkit::utils::random::RandomEngine::get_float(
                0,
                PIX2
            );
            float speed = bnjkit::utils::random::RandomEngine::get_float(
                0,
                m_bot_max_speed
            );
            sf::Vector2f direction =
                    bnjkit::utils::d2::rad_to_vec(angle_rnd);
            sf::Vector2f velocity = direction * speed;
            evobot->set_velocity(velocity);
        }
        for (unsigned int i = 0; i < start_glob; ++ i) {
            auto glob = m_entity_manager->create<Glob>();
            float radius = bnjkit::utils::random::RandomEngine::get_float(
                m_glob_min_radius,
                m_glob_max_radius
            );
            glob->set_radius(radius);
            D2::Position position;
            position.x = bnjkit::utils::random::RandomEngine::get_float(
                0.f,
                m_play_ground->size.x
            );
            position.y = bnjkit::utils::random::RandomEngine::get_float(
                0.f,
                m_play_ground->size.y
            );
            glob->set_position(position);
            float angle_rnd = bnjkit::utils::random::RandomEngine::get_float(
                0,
                PIX2
            );
            float speed = bnjkit::utils::random::RandomEngine::get_float(
                0,
                m_glob_max_speed
            );
            sf::Vector2f direction =
                    bnjkit::utils::d2::rad_to_vec(angle_rnd);
            sf::Vector2f velocity = direction * speed;
            glob->set_velocity(velocity);
        }
        m_state = State::READY;
    }
    void EvobotEngine::clear() {
        m_play_ground.reset();
        m_entity_manager->clear();
    }
    void EvobotEngine::update() {
        m_play_ground->update();
        auto [evobots, globs] = m_entity_manager->get<Evobot, Glob>();
        for (auto& evobot: evobots.get().entities()) {
            evobot->update();
        }
        for (auto& glob: globs.get().entities()) {
            glob->update();
        }
    }

    bnjkit::entity::EntityManager& EvobotEngine::entity_manager() {
        return * m_entity_manager;
    }
    const bnjkit::entity::EntityManager& EvobotEngine::entity_manager() const {
        return * m_entity_manager;
    }

    std::string EvobotEngine::name() const {
        return "EvobotEngine";
    }

    void EvobotEngine::on_sfml_event(const sf::Event& event[[maybe_unused]]) {}
}
