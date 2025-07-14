/*!
 * @author bintjeman
 * @date 13.07.25
 * @name evo_world.cpp
 */

#include "evo_world.hpp"
#include <bintjekit/configuration/sfml_json_adapter.hpp>
#include <bintjekit/engine/play_ground.hpp>
#include "bintjekit/utils/random/random_engine.hpp"
#include "evobot_engine/components/components.hpp"
#include "spdlog/logger.h"

namespace evo::engine {
    EvoWorld::EvoWorld() : World("EvoWorld") {
        m_logger->info("EvoWorld: created");
    }
    EvoWorld::~EvoWorld() {
        m_logger->info("EvoWorld: destroyed");
    }
    void EvoWorld::initialization() {
        m_logger->info("EvoWorld: initializing");
        init_prefab();
    }
    void EvoWorld::init_prefab() {
        m_logger->info("EvoWorld: initializing prefab");
        // Prefab pour Evobot
        register_prefab("evobot", {
                            .spawn = [this](bnjkit::engine::World& world) -> entt::entity {
                                auto entity = world.registry().create();

                                // Composants de base
                                world.registry().emplace<comp::D2>(entity,
                                                                   sf::Vector2f{100.f, 100.f},
                                                                   m_bot_min_radius
                                );
                                world.registry().emplace<comp::Velocity>(entity);
                                world.registry().emplace<comp::EvobotTag>(entity);
                                world.registry().emplace<comp::Health>(entity, 60.f, 60.f);

                                // Composants optionnels
                                if (bnjkit::utils::random::RandomEngine::get_bool()) {
                                    sf::Color color{
                                        static_cast<unsigned char>(
                                            bnjkit::utils::random::RandomEngine::get_int(0, 255)),
                                        static_cast<unsigned char>(
                                            bnjkit::utils::random::RandomEngine::get_int(0, 255)),
                                        static_cast<unsigned char>(bnjkit::utils::random::RandomEngine::get_int(0, 255))
                                    };
                                    world.registry().emplace<comp::Arrow>(entity, color, 20.f);
                                }

                                return entity;
                            },
                            .name = "evobot"
                        });

        // Prefab pour Glob
        register_prefab("glob", {
                            .spawn = [this](bnjkit::engine::World& world) -> entt::entity {
                                auto entity = world.registry().create();

                                // Composants de base
                                world.registry().emplace<comp::D2>(entity,
                                                                   sf::Vector2f{0.f, 0.f},
                                                                   m_glob_min_radius
                                );
                                world.registry().emplace<comp::Velocity>(entity);
                                world.registry().emplace<comp::GlobTag>(entity);

                                // Composant optionnel
                                if (bnjkit::utils::random::RandomEngine::get_bool()) {
                                    world.registry().emplace<comp::Health>(entity, 30.f, 30.f);
                                }

                                return entity;
                            },
                            .name = "glob"
                        });
    }
    void EvoWorld::set_settings(bnjkit::conf::Node& settings) {
        m_logger->debug("EvoWorld: setting settings");
        m_settings = settings;
    }
    void EvoWorld::configure(bnjkit::conf::Node settings) {
        if (!settings.get_json().is_null()) {
            set_settings(settings);
        }
        m_logger->debug("EvoWorld: configuring");
        m_bot_max_radius = settings.get_or_set("/Rules/Bot/Max radius", 20.f);
        m_bot_min_radius = settings.get_or_set("/Rules/Bot/Min radius", 10.f);
        m_bot_max_speed = settings.get_or_set("/Rules/Bot/Max speed", 10.f);
        m_maximum_bot = settings.get_or_set("/Rules/Bot/Max bots", 1000);
        m_minimum_bot = settings.get_or_set("/Rules/Bot/Min bots", 100);
        m_glob_max_radius = settings.get_or_set("/Rules/Glob/Max radius", 20.f);
        m_glob_min_radius = settings.get_or_set("/Rules/Glob/Min radius", 10.f);
        m_glob_max_speed = settings.get_or_set("/Rules/Glob/Max speed", 10.f);
        m_maximum_glob = settings.get_or_set("/Rules/Glob/Max globs", 1000);
        m_minimum_glob = settings.get_or_set("/Rules/Glob/Ming globs", 100);;
    }
    void EvoWorld::generate() {
        m_logger->info("EvoWorld: generating");
        generate_playground();
        unsigned int initial_bots = bnjkit::utils::random::RandomEngine::get_int(
            m_minimum_bot,
            m_maximum_bot
        );
        for (unsigned int i = 0; i < initial_bots; ++ i) {
            spawn_prefab("evobot");
        }
        // Génération des globs initiaux
        unsigned int initial_globs = bnjkit::utils::random::RandomEngine::get_int(
            m_minimum_glob,
            m_maximum_glob
        );
        for (unsigned int i = 0; i < initial_globs; ++ i) {
            spawn_prefab("glob");
        }
    }
    void EvoWorld::generate_playground() {
        m_logger->info("EvoWorld: generating playground");
        auto playground_bounds = m_settings.get_or_set<sf::Rect<float> >(
            "/Rules/Playground/Bounds", {{-500.f, -500.f}, {500.f, 500.f}});
        m_play_ground->size = playground_bounds.size;
        m_play_ground->position = playground_bounds.position;
    }
}
