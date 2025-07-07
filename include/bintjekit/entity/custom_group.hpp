/*!
 * @author bintjeman
 * @date 06.07.25
 * @name customgroup.hpp
 */
// customgroup.hpp
#ifndef BINTJEKIT_ENTITY_CUSTOMGROUP_HPP
#define BINTJEKIT_ENTITY_CUSTOMGROUP_HPP
#pragma once

#include <string>
#include <unordered_set>

namespace bnjkit::entity {
    template<typename BaseEntity>
    requires std::derived_from<BaseEntity, IEntity>
    class EntityManager;

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    class CustomGroup {
    public:
        using GroupId = std::string;

        CustomGroup(EntityManager<BaseEntity>& manager, const GroupId& id);

        void add(EntityId entityId);
        void remove(EntityId entityId);
        [[nodiscard]] const GroupId& id() const;
        [[nodiscard]] size_t size() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] bool contains(EntityId id) const;

        template<typename T = BaseEntity>
        class Iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::shared_ptr<T>;

            Iterator(std::unordered_set<EntityId>::const_iterator it,
                     const std::unordered_set<EntityId>& ids,
                     EntityManager<BaseEntity>& manager);
            value_type operator*();
            Iterator& operator++();
            bool operator!=(const Iterator& other) const;

        private:
            void findNextValid();
            std::unordered_set<EntityId>::const_iterator m_current;
            std::unordered_set<EntityId>::const_iterator m_end;
            EntityManager<BaseEntity>& m_manager;
        };

        template<typename T = BaseEntity>
        Iterator<T> begin();

        template<typename T = BaseEntity>
        Iterator<T> end();

    private:
        EntityManager<BaseEntity>& m_entityManager;
        GroupId m_group_id;
        std::unordered_set<EntityId> m_entity_ids;
    };
}

#include "custom_group.inl"
#endif
