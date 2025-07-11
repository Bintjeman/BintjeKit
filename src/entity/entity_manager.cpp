/*!
 * @author bintjeman
 * @date 08.07.25
 * @name entity_manager.cpp
 */

#include "bintjekit/entity/entity_manager.hpp"
#include <bintjekit/logger/logger.hpp>
#include "bintjekit/core/common.hpp"

namespace bnjkit::entity {
    EntityManager::EntityManager() {
        m_logger = core::Logger::get_logger(bnjkit::core::module_names::ENTITY);
    }

    EntityManager::~EntityManager() {}

    void EntityManager::mark_for_removal(EntityId id) {
        m_pending_removals.push_back(id);
    }
    void EntityManager::process_pending_removals() {
        for (auto id: m_pending_removals) {
            if (m_entity_types.contains(id)) {
                const auto entity_type = m_entity_types.find(id)->second;
                if (m_collections.contains(entity_type)) {
                    auto& collection = * static_cast<TypedCollection<IEntity>*>(m_collections.at(entity_type).
                        get());
                    // Supprime les composants associés
                    for (auto& [type, registry]: m_component_registries) {
                        registry->remove(id);
                    }
                    collection.remove(id);
                    m_entity_types.erase(id);
                }
            }
        }
        m_pending_removals.clear();
    }
    void EntityManager::clear() {
        for (auto& [type, collection]: m_collections) {
            collection->clear();
        }
        for (auto& [type, registry]: m_component_registries) {
            registry->clear();
        }
    }
    std::size_t EntityManager::size() const {
        std::size_t size = 0;
        for (const auto& collection: m_collections) {
            size += collection.second->size();
        }
        return size;
    }
    void EntityManager::remove(const EntityId id) {
        if (m_entity_types.contains(id)) {
            const auto entity_type = m_entity_types.find(id)->second;
            if (m_collections.contains(entity_type)) {
                auto& collection = * static_cast<TypedCollection<IEntity>*>(m_collections.at(entity_type)
                    .get());
                collection.remove(id);
            }
            m_logger->warn("Collection {} does not exist", entity_type.name());
        }
        m_logger->warn("Entity {} does not exist", id);
    }
}
