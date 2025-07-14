/*!
 * @author bintjeman
 * @date 13.07.25
 * @name entity_manager.cpp
 */

#include "bintjekit/engine/entity_manager.hpp"
#include "bintjekit/logger.hpp"

namespace bnjkit::engine {
    EntityManager::EntityManager() {
        m_logger = core::Logger::get_logger(core::module_names::ENTITY);
        m_logger->info("EntityManager created");
    }
    entt::registry& EntityManager::registry() { return m_registry; }
    const entt::registry& EntityManager::registry() const { return m_registry; }
    void EntityManager::destroy(entt::entity entity) {
        m_registry.destroy(entity);
    }
    void EntityManager::clear() {
        m_registry.clear();
    }
}
