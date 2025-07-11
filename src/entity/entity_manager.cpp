/*!
 * @author bintjeman
 * @date 08.07.25
 * @name entity_manager.cpp
 */

#include "bintjekit/entity/entity_manager.hpp"

#include <ranges>
#include <bintjekit/logger/logger.hpp>
#include "bintjekit/core/common.hpp"

namespace bnjkit::entity {
    EntityManager::EntityManager() {
        m_logger = core::Logger::get_logger(core::module_names::ENTITY);
    }

    EntityManager::~EntityManager() = default;

    void EntityManager::mark_for_removal(const EntityId id) {
        m_pending_removals.push_back(id);
    }
    void EntityManager::process_pending_removals() {
        for (auto id: m_pending_removals) {
            if (m_entity_types.contains(id)) {
                if (const auto entity_type = m_entity_types.find(id)->second; m_collections.contains(entity_type)) {
                    auto& collection = * static_cast<TypedCollection<IEntity>*>(m_collections.at(entity_type).
                        get());
                    // Supprime les composants associés
                    for (const auto& registry: m_component_registries | std::views::values) {
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
        for (const auto& collection: m_collections | std::views::values) {
            collection->clear();
        }
        for (const auto& registry: m_component_registries | std::views::values) {
            registry->clear();
        }
    }
    std::size_t EntityManager::size() const {
        std::size_t size = 0;
        for (const auto& collection: m_collections | std::views::values) {
            size += collection->size();
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
