/*!
 * @author bintjeman
 * @date 06.07.25
 * @name customgroup.inl
 */
// customgroup.inl
#ifndef BINTJEKIT_ENTITY_CUSTOMGROUP_INL
#define BINTJEKIT_ENTITY_CUSTOMGROUP_INL
#pragma once

#include "bintjekit/entity/entitymanager.hpp"

namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    CustomGroup<BaseEntity>::CustomGroup(EntityManager<BaseEntity>& manager, const GroupId& id)
        : m_entityManager(manager)
          , m_group_id(id) {
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
        return Iterator<T>(m_entity_ids.begin(), m_entity_ids, m_entityManager);
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
    typename CustomGroup<BaseEntity>::template Iterator<T>
    CustomGroup<BaseEntity>::end() {
        return Iterator<T>(m_entity_ids.end(), m_entity_ids, m_entityManager);
    }
}
#endif
