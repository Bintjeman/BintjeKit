/*!
 * @author bintjeman
 * @date 13.07.25
 * @name world.cpp
 */
#include "bintjekit/engine/i_world.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/engine/play_ground.hpp"
#include "bintjekit/ecs/event/event_manager.hpp"
#include "bintjekit/ecs/prefab/prefab.hpp"
#include "bintjekit/ecs/system/i_system.hpp"

namespace bnjkit::ecs {
    IWorld::IWorld(const std::string& name): EntityManager(), m_name(name)
                                             , m_eventBus(std::make_unique<EventBus>()) {
        m_logger->info("World '{}' created", name);
        m_play_ground = std::make_unique<PlayGround>();
    }
    IWorld::~IWorld() {
        m_logger->info("World '{}' destroyed", m_name);
        for (auto it = m_systems.rbegin(); it != m_systems.rend(); ++ it) {
            (* it)->cleanup(* this);
        }
    }
    void IWorld::update() {
        // Update des systèmes
        for (auto& system: m_systems) {
            system->update(* this);
        }
    }
    void IWorld::register_prefab(const std::string& name, PrefabData data) {
        m_prefabs[name] = std::move(data);
    }
    entt::entity IWorld::spawn_prefab(const std::string& name) {
        auto it = m_prefabs.find(name);
        if (it != m_prefabs.end()) {
            return it->second.spawn(* this);
        }
        m_logger->error("Prefab '{}' not found", name);
        return entt::null;
    }
    std::string IWorld::name() const {
        return "IWorld";
    }
    PlayGround& IWorld::play_ground() {
        return * m_play_ground;
    }
    const PlayGround& IWorld::play_ground() const {
        return * m_play_ground;
    }
}
