/*!
 * @author bintjeman
 * @date 13.07.25
 * @name world.cpp
 */

#include "bintjekit/engine/world.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/engine/play_ground.hpp"
#include "bintjekit/engine/event/event_manager.hpp"
#include "bintjekit/engine/system/i_system.hpp"

namespace bnjkit::engine {
    World::World(const std::string& name): EntityManager(), m_name(name)
                                           , m_eventBus(std::make_unique<EventBus>()) {
        m_logger->info("World '{}' created", name);
        m_play_ground = std::make_unique<PlayGround>();
    }
    World::~World() {
        m_logger->info("World '{}' destroyed", m_name);
        for (auto it = m_systems.rbegin(); it != m_systems.rend(); ++ it) {
            (* it)->cleanup(* this);
        }
    }
    void World::update() {
        // Update des systèmes
        for (auto& system: m_systems) {
            system->update(* this);
        }
    }
    void World::register_prefab(const std::string& name, PrefabData data) {
        m_prefabs[name] = std::move(data);
    }
    entt::entity World::spawn_prefab(const std::string& name) {
        auto it = m_prefabs.find(name);
        if (it != m_prefabs.end()) {
            return it->second.spawn(* this);
        }
        m_logger->error("Prefab '{}' not found", name);
        return entt::null;
    }
    const std::string& World::name() const {
        return m_name;
    }
    PlayGround& World::play_ground() {
        return *m_play_ground;
    }
    const PlayGround& World::play_ground() const {
        return *m_play_ground;
    }
}
