/*!
 * @author bintjeman
 * @date 26.06.25
 * @name collection.cpp
 */
#include "bintjekit/entity/collection.hpp"

namespace bnjkit {
    namespace entity {
        ICollection::ICollection() {
        }
        ICollection::~ICollection() {
        }
        void ICollection::add_entity(Entity entity) {
            auto index = m_collection.size();
            m_collection.push_back(entity);
            m_registry.emplace(entity.id(), index);
        }
        void ICollection::remove_entity(EntityRef entity) {
            remove_entity(entity.get().id());
        }
        void ICollection::remove_entity(const EntityPtr& entity) {
            remove_entity(entity->id());
        }
        void ICollection::remove_entity(EntityId id) {
            auto it = m_registry.find(id);
            if (it != m_registry.end()) {
                m_collection[it->second] = m_collection.back();
                m_collection.pop_back();
                m_registry.erase(id);
            }
        }
        void ICollection::clear() {
            m_collection.clear();
            m_registry.clear();
        }
        EntityCollection& ICollection::get_collection() {
            return m_collection;
        }
        EntityRegystry& ICollection::get_registry() {
            return m_registry;
        }
        EntityRef ICollection::get_entity(EntityId id) {
            auto it = m_registry.find(id);
            if (it != m_registry.end()) {
                return std::ref(m_collection[it->second]);
            }
            throw std::runtime_error("Entity not found");
        }
        EntityIndex ICollection::get_entity_index(EntityId id) {
            auto it = m_registry.find(id);
            return it->second;
        }
    } // entity
} // bnjkit
