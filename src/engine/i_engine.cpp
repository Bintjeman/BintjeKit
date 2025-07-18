/*!
 * @author bintjeman
 * @date 13.07.25
 * @name world.cpp
 */
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/ecs/prefab/prefab.hpp"
#include "bintjekit/engine/play_ground.hpp"

namespace bnjkit::engine {
    IEngine::IEngine() {
        m_logger = core::Logger::get_logger(literals::logger::ENGINE);
        m_logger->info("IEngine created");
        m_play_ground = std::make_unique<PlayGround>();
    }
    IEngine::~IEngine() {
        m_logger->info("IEngine destroyed");
    }
    void IEngine::register_prefab(const std::string& name, ecs::PrefabData data) {
        m_prefabs.emplace(name, std::move(data));
    }
    entt::entity IEngine::spawn_prefab(const std::string& name) {
        auto it = m_prefabs.find(name);
        if (it != m_prefabs.end()) {
            return it->second.spawn(* this);
        }
        m_logger->error("Prefab '{}' non trouvé", name);
        return entt::null;
    }
    void IEngine::update() {}
    PlayGround& IEngine::play_ground() {
        return * m_play_ground;
    }
    const PlayGround& IEngine::play_ground() const {
        return * m_play_ground;
    }
}
