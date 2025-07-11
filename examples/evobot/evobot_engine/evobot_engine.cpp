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
#include <bintjekit/entity/entity_manager.hpp>

#include "components/arrow_component.hpp"
#include "components/health.hpp"
// #include "evobot_engine/entity.hpp"
#include "evobot_engine/evobot.hpp"
#include "evobot_engine/glob.hpp"
#include "evobot_engine/components/d2.hpp"

namespace evo::engine {
    EvobotEngine::EvobotEngine() {
        m_logger->info("EvobotEngine: created");
        m_entity_manager = std::make_unique<evo::entity::EvoEntityManager>();
        // entity_manager().create_collection<Evobot>();
        // entity_manager().create_collection<Glob>();
        // entity_manager().register_component<entity::ArrowComponent>();
        // entity_manager().register_component<entity::Health>();
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
        // entity_manager().create_collection<Evobot>();
        // entity_manager().create_collection<Glob>();
        // entity_manager().register_component<entity::ArrowComponent>();
        // entity_manager().register_component<entity::Health>();
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
            bool random = bnjkit::utils::random::RandomEngine::get_bool();
            if (random) {
                unsigned char r = bnjkit::utils::random::RandomEngine::get_int(0, 255);
                unsigned char g = bnjkit::utils::random::RandomEngine::get_int(0, 255);
                unsigned char b = bnjkit::utils::random::RandomEngine::get_int(0, 255);
                sf::Color color = sf::Color{r, g, b};
                entity_manager().add_component(evobot->id(), entity::ArrowComponent{color, 20.f});
                auto has_health = bnjkit::utils::random::RandomEngine::get_bool();
                if (has_health) {
                    entity_manager().add_component(evobot->id(), entity::Health{60.f});
                } else {}
            } else {}
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
            auto has_health = bnjkit::utils::random::RandomEngine::get_bool();
            if (has_health) {
                entity_manager().add_component(glob->id(), entity::Health{30.f});
            } else {}
        }
        m_state = State::READY;
    }
    void EvobotEngine::clear() {
        m_play_ground.reset();
        m_entity_manager->clear();
    }
    void EvobotEngine::update() {
        auto& health_registry = entity_manager().get_component_registry<entity::Health>();
        m_play_ground->update();
        auto [evobots, globs] = m_entity_manager->get_collections<Evobot, Glob>();
        for (auto& evobot: evobots.get().entities()) {
            if (evobot->is_active()) {
                evobot->update();
            }
        }
        for (auto& glob: globs.get().entities()) {
            if (glob->is_active()) {
                glob->update();
            }
        }

        auto health_view = evobots.get().create_view().where([&health_registry](const auto& entity) {
            return health_registry.has(entity->id());
        }).build();
        for (auto entity: health_view) {
            if (entity->is_active()) {
                auto* health = health_registry.get(entity->id());
                health->damage(1.f);
                if (health->current() <= 0.f) {
                    m_logger->debug("kill: {}", entity->id());
                    entity->set_state(bnjkit::entity::EntityState::DEAD);
                    entity_manager().mark_for_removal(entity->id());
                }
            }
        }
        entity_manager().process_pending_removals();
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
