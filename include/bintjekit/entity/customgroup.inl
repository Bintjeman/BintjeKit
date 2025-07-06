/*!
 * @author bintjeman
 * @date 06.07.25
 * @name customgroup.inl
 */

#ifndef BINTJEKIT_ENTITY_CUSTOMGROUP_INL
#define BINTJEKIT_ENTITY_CUSTOMGROUP_INL
#pragma once
#include "bintjekit/entity/entitymanager.hpp"
namespace bnjkit {
    namespace entity {
        template<typename T>
        class CustomGroup::Iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::shared_ptr<T>;

            Iterator(std::unordered_set<EntityId>::const_iterator it,
                     const std::unordered_set<EntityId>& ids,
                     EntityManager& manager)
                : m_current(it), m_end(ids.end()), m_manager(manager) {
                findNextValid();
            }
            value_type operator*() {
                return m_manager.get<T>(* m_current);
            }
            Iterator& operator++() {
                ++ m_current;
                findNextValid();
                return * this;
            }
            bool operator!=(const Iterator& other) const {
                return m_current != other.m_current;
            }
        private:
            void findNextValid() {
                while (m_current != m_end) {
                    try {
                        m_manager.get<T>(* m_current);
                        break;
                    } catch (...) {
                        ++ m_current;
                    }
                }
            }
            std::unordered_set<EntityId>::const_iterator m_current;
            std::unordered_set<EntityId>::const_iterator m_end;
            EntityManager& m_manager;
        };
        template<typename T>
        CustomGroup::Iterator<T> CustomGroup::begin() {
            return Iterator<T>(m_entity_ids.begin(), m_entity_ids, m_entityManager);
        }
        template<typename T>
        CustomGroup::Iterator<T> CustomGroup::end() {
            return Iterator<T>(m_entity_ids.end(), m_entity_ids, m_entityManager);
        }
    } // entity
} // bnjkit

#endif //BINTJEKIT_ENTITY_CUSTOMGROUP_INL
