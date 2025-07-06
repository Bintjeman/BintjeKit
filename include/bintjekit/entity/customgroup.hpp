/*!
 * @author bintjeman
 * @date 06.07.25
 * @name customgroup.hpp
 */

#ifndef BINTJEKIT_ENTITY_CUSTOMGROUP_HPP
#define BINTJEKIT_ENTITY_CUSTOMGROUP_HPP
#pragma once
#include <string>
#include <unordered_set>
#include "bintjekit/entity/entity_helper.hpp"
namespace bnjkit {
    namespace entity {
        class EntityManager; // Forward declaration
        class CustomGroup {
        public:
            using GroupId = std::string;
            CustomGroup(EntityManager& manager, const GroupId& id);
            void add(EntityId entityId);
            void remove(EntityId entityId);
            const GroupId& id() const;
            size_t size() const;
            bool empty() const;
            bool contains(EntityId id) const;
            template<typename T = IEntity>
            class Iterator;
            template<typename T = IEntity>
            Iterator<T> begin();
            template<typename T = IEntity>
            Iterator<T> end();

        private:
            EntityManager& m_entityManager;
            GroupId m_group_id;
            std::unordered_set<EntityId> m_entity_ids;
        };
    } // entity
} // bnjkit
#endif // BINTJEKIT_ENTITY_CUSTOMGROUP_HPP
