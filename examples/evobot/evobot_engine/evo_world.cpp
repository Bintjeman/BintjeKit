/*!
 * @author bintjeman
 * @date 13.07.25
 * @name evo_world.cpp
 */

#include "evo_world.hpp"
#include <bintjekit/configuration/node.hpp>

#include "bintjekit/utils/random/random_engine.hpp"
#include "evobot_engine/components/components.hpp"

namespace evo::engine {
    EvoWorld::EvoWorld() : World("EvoWorld") {
        init_prefab();
    }
    EvoWorld::~EvoWorld() {}
    void EvoWorld::init_prefab() {
        // Prefab pour Evobot
        register_prefab("evobot", {
                            .spawn = [this](bnjkit::engine::World& world) -> entt::entity {
                                auto entity = world.registry().create();

                                // Composants de base
                                world.registry().emplace<comp::D2>(entity,
                                                                   sf::Vector2f{0.f, 0.f},
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
    void EvoWorld::configure(bnjkit::conf::Node& settings) {
        m_bot_max_radius = settings.get_or_set("/Rules/Bot/MaxRadius", 20.f);
        m_bot_min_radius = settings.get_or_set("/Rules/Bot/MinRadius", 10.f);
        m_bot_max_speed = settings.get_or_set("/Rules/Bot/MaxSpeed", 10.f);
        m_maximum_bot = settings.get_or_set("/Rules/Bot/MaxBots", 1000.f);
        m_minimum_bot = settings.get_or_set("/Rules/Bot/MinBots", 100.f);
        m_glob_max_radius = settings.get_or_set("/Rules/Glob/MaxRadius", 20.f);
        m_glob_min_radius = settings.get_or_set("/Rules/Glob/MinRadius", 10.f);
        m_glob_max_speed = settings.get_or_set("/Rules/Glob/MaxSpeed", 10.f);
        m_maximum_glob = settings.get_or_set("/Rules/Glob/MaxGlobs", 1000.f);
        m_minimum_glob = settings.get_or_set("/Rules/Glob/MinGlobs", 100.f);
    }
    void EvoWorld::generate() {
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
}
