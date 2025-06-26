/*!
 * @author bintjeman
 * @date 26.06.25
 * @name collection.cpp
 */
#include "bintjekit/entity/group.hpp"

namespace bnjkit {
    namespace entity {
        IGroup::IGroup() {
        }
        IGroup::~IGroup() {
        }
        void IGroup::add_entity(EntityPtr entity) {
            auto index = m_collection.size();
            m_collection.push_back(entity);
            m_registry.emplace(entity->id(), index);
        }
        void IGroup::remove_entity(EntityPtr entity) {
            auto EntityId = entity->id();
            auto it = m_registry.find(EntityId);
            if (it != m_registry.end()) {
                m_collection[it->second] = m_collection.back();
                m_collection.pop_back();
                m_registry.erase(EntityId);
            }
        }
        void IGroup::clear() {
            m_collection.clear();
            m_registry.clear();
        }
        EntityCollection& IGroup::get_collection() {
            return m_collection;
        }
        EntityRegystry& IGroup::get_registry() {
            return m_registry;
        }
        EntityPtr IGroup::get_entity(EntityId id) {
            auto it = m_registry.find(id);
            if (it != m_registry.end()) {
                return m_collection[it->second];
            }
            return nullptr;
        }
        EntityIndex IGroup::get_entity_index(EntityId id) {
            auto it = m_registry.find(id);
            return it->second;
        }
    } // entity
} // bnjkit
