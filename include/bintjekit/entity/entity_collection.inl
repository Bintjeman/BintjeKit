/*!
 * @author bintjeman
 * @date 07.07.25
 * @name entity_collection.inl
 */

#ifndef ENTITY_COLLECTION_INL
#define ENTITY_COLLECTION_INL
#pragma once

#include "entity_collection.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"

namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    std::shared_ptr<spdlog::logger> EntityCollectionManager<BaseEntity>::m_logger =
            core::get_logger(core::module_names::ENTITY);

    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    void EntityCollectionManager<BaseEntity>::add(EntityPtr entity) {
        if (!entity) {
            m_logger->error("Tentative d'ajout d'une entité nulle");
            return;
        }

        auto id = entity->id();
        if (m_registry.find(id) == m_registry.end()) {
            m_registry[id] = entity;
            m_entities.push_back(entity);
        } else {
            m_logger->error("L'entité avec l'id {} existe déjà", id);
        }
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    typename EntityCollectionManager<BaseEntity>::EntityPtr
    EntityCollectionManager<BaseEntity>::create(EntityId id) {
        auto entity = std::make_shared<BaseEntity>(id);
        add(entity);
        return entity;
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    typename EntityCollectionManager<BaseEntity>::EntityPtr
    EntityCollectionManager<BaseEntity>::get(EntityId id) {
        auto it = m_registry.find(id);
        return (it != m_registry.end()) ? it->second : nullptr;
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    void EntityCollectionManager<BaseEntity>::remove(EntityId id) {
        auto it = m_registry.find(id);
        if (it != m_registry.end()) {
            auto entity = it->second;
            m_registry.erase(it);
            m_entities.erase(
                std::remove(m_entities.begin(), m_entities.end(), entity),
                m_entities.end()
            );
        }
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    void EntityCollectionManager<BaseEntity>::clear() {
        m_entities.clear();
        m_registry.clear();
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    std::size_t EntityCollectionManager<BaseEntity>::size() const {
        return m_entities.size();
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    const typename EntityCollectionManager<BaseEntity>::EntityCollection&
    EntityCollectionManager<BaseEntity>::get_entities() const {
        return m_entities;
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    const typename EntityCollectionManager<BaseEntity>::EntityRegistry&
    EntityCollectionManager<BaseEntity>::get_registry() const {
        return m_registry;
    }
}
#endif //ENTITY_COLLECTION_INL
