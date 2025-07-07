/*!
 * @author bintjeman
 * @date 06.07.25
 * @name customgroup.inl
 */
// customgroup.inl
#ifndef BINTJEKIT_ENTITY_CUSTOM_GROUP_INL
#define BINTJEKIT_ENTITY_CUSTOM_GROUP_INL
#pragma once
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/core/common.hpp"

namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    std::shared_ptr<spdlog::logger> CustomGroup<BaseEntity>::m_logger = core::Logger::get_logger(
        core::module_names::ENTITY);

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    CustomGroup<BaseEntity>::CustomGroup(EntityManager<BaseEntity>& manager, const GroupId& id)
        : m_entity_manager(manager)
          , m_group_id(std::move(id)) {}

    template<typename BaseEntity> requires std::derived_from<BaseEntity, IEntity>
    void CustomGroup<BaseEntity>::add(const EntityId entity_id) {
        if (!m_entity_ids.contains(entity_id)) {
            m_entity_ids.insert(entity_id);
        } else {
            m_logger->warn("Entity already in group: {}", entity_id);
        }
    }

    template<typename BaseEntity> requires std::derived_from<BaseEntity, IEntity>
    void CustomGroup<BaseEntity>::remove(EntityId entity_id) {
        if (m_entity_ids.contains(entity_id)) {
            m_entity_ids.erase(entity_id);
        }else {
            m_logger->warn("Entity not in group: {}", entity_id);
        }
    }

    template<typename BaseEntity> requires std::derived_from<BaseEntity, IEntity>
    const typename CustomGroup<BaseEntity>::GroupId& CustomGroup<BaseEntity>::id() const {
        return m_group_id;
    }

    template<typename BaseEntity> requires std::derived_from<BaseEntity, IEntity>
    size_t CustomGroup<BaseEntity>::size() const {
        return m_entity_ids.size();
    }

    template<typename BaseEntity> requires std::derived_from<BaseEntity, IEntity>
    bool CustomGroup<BaseEntity>::empty() const {
        return m_entity_ids.empty();
    }

    template<typename BaseEntity> requires std::derived_from<BaseEntity, IEntity>
    bool CustomGroup<BaseEntity>::contains(EntityId id) const {
        return m_entity_ids.contains(id);
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
    CustomGroup<BaseEntity>::Iterator<T>::Iterator(
        std::unordered_set<EntityId>::const_iterator it,
        const std::unordered_set<EntityId>& ids,
        EntityManager<BaseEntity>& manager)
        : m_current(it)
          , m_end(ids.end())
          , m_manager(manager) {
        findNextValid();
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
    typename CustomGroup<BaseEntity>::template Iterator<T>::value_type
    CustomGroup<BaseEntity>::Iterator<T>::operator*() {
        return m_manager.template get<T>(* m_current);
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
    typename CustomGroup<BaseEntity>::template Iterator<T>&
    CustomGroup<BaseEntity>::Iterator<T>::operator++() {
        ++ m_current;
        findNextValid();
        return * this;
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
    bool CustomGroup<BaseEntity>::Iterator<T>::operator!=(const Iterator& other) const {
        return m_current != other.m_current;
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
    void CustomGroup<BaseEntity>::Iterator<T>::findNextValid() {
        while (m_current != m_end) {
            try {
                m_manager.template get<T>(* m_current);
                break;
            } catch (...) {
                ++ m_current;
            }
        }
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
    typename CustomGroup<BaseEntity>::template Iterator<T>
    CustomGroup<BaseEntity>::begin() {
        return Iterator<T>(m_entity_ids.begin(), m_entity_ids, m_entity_manager);
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
    typename CustomGroup<BaseEntity>::template Iterator<T>
    CustomGroup<BaseEntity>::end() {
        return Iterator<T>(m_entity_ids.end(), m_entity_ids, m_entity_manager);
    }
}
#endif
