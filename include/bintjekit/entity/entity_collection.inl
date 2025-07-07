/*!
 * @author bintjeman
 * @date 07.07.25
 * @name entity_collection.inl
 */

#ifndef ENTITY_COLLECTION_INL
#define ENTITY_COLLECTION_INL
#pragma once

#include "bintjekit/entity/entity_collection.hpp"
#include "bintjekit/entity/entity_helper.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"

namespace bnjkit::entity {
    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    std::shared_ptr<spdlog::logger> EntityCollectionManager<BaseEntity>::m_logger = core::Logger::get_logger(
        core::module_names::ENTITY);

    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    EntityCollectionManager<BaseEntity>::EntityCollectionManager() = default;

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    void EntityCollectionManager<BaseEntity>::add(const EntityPtr& entity) {
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

    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    EntityPtr EntityCollectionManager<BaseEntity>::create() {
        auto entity = std::make_shared<BaseEntity>();
        add(entity);
        return entity;
    }

    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    EntityPtr EntityCollectionManager<BaseEntity>::get(EntityId id) {
        auto it = m_registry.find(id);
        return (it != m_registry.end()) ? it->second : nullptr;
    }
    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    const EntityPtr EntityCollectionManager<BaseEntity>::get(EntityId id) const {
        auto it = m_registry.find(id);
        return (it != m_registry.end()) ? it->second : nullptr;
    }
    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    void EntityCollectionManager<BaseEntity>::remove(EntityId id) {
        auto registry_it = m_registry.find(id);
        if (registry_it != m_registry.end()) {
            auto entity_it = std::find_if(m_entities.begin(), m_entities.end(),
                                          [id](const EntityPtr& e) { return e && e->id() == id; });

            if (entity_it != m_entities.end()) {
                if (entity_it != m_entities.end() - 1) {
                    * entity_it = std::move(m_entities.back());
                }
                m_entities.pop_back();
            }

            m_registry.erase(registry_it);
        }
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    void EntityCollectionManager<BaseEntity>::clear() {
        m_entities.clear();
        m_registry.clear();
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    std::size_t EntityCollectionManager<BaseEntity>::size() const {
        return m_entities.size();
    }
    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    EntityCollection EntityCollectionManager<BaseEntity>::get_entities() const {
        return m_entities;
    }
    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    EntityCollection EntityCollectionManager<BaseEntity>::get_entities() {
        return m_entities;
    }
    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    EntityRegistry EntityCollectionManager<BaseEntity>::get_registry() const {
        return m_registry;
    }
    template<typename BaseEntity> requires std::is_base_of_v<IEntity, BaseEntity>
    EntityRegistry EntityCollectionManager<BaseEntity>::get_registry() {
        return m_registry;
    }
}
#endif //ENTITY_COLLECTION_INL
