/*!
 * @author bintjeman
 * @date 13.07.25
 * @name entity_manager.cpp
 */
#include "bintjekit/ecs/entity_manager.hpp"
namespace bnjkit::ecs {
    EntityManager::EntityManager() = default;
    EntityManager::~EntityManager() = default;
    entt::registry& EntityManager::registry() { return m_registry; }
    const entt::registry& EntityManager::registry() const { return m_registry; }
    void EntityManager::destroy(entt::entity entity) {
        m_registry.destroy(entity);
    }
    void EntityManager::clear() {
        m_registry.clear();
    }
}
