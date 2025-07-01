/*!
 * @author bintjeman
 * @date 26.06.25
 * @name collection.cpp
 */
#include "bintjekit/entity/collection.hpp"

namespace bnjkit {
    namespace entity {
        Collection::Collection() {
        }
        Collection::~Collection() {
        }
        void Collection::add_entity(Entity&& entity) {
            auto index = m_collection.size();
            m_collection.push_back(std::move(entity));
            m_registry.emplace(entity.id(), index);
        }
        void Collection::remove_entity(EntityRef entity) {
            remove_entity(entity.get().id());
        }
        void Collection::remove_entity(const EntityPtr& entity) {
            remove_entity(entity->id());
        }
        void Collection::remove_entity(EntityId id) {
            auto it = m_registry.find(id);
            if (it != m_registry.end()) {
                m_collection[it->second] = std::move(m_collection.back());
                m_collection.pop_back();
                m_registry.erase(id);
            }
        }
        void Collection::clear() {
            m_collection.clear();
            m_registry.clear();
        }
        EntityCollection& Collection::get_collection() {
            return m_collection;
        }
        const EntityCollection& Collection::get_collection() const {
            return m_collection;
        }
        EntityRegystry& Collection::get_registry() {
            return m_registry;
        }
        EntityRef Collection::get_entity(EntityId id) {
            auto it = m_registry.find(id);
            if (it != m_registry.end()) {
                return std::ref(m_collection[it->second]);
            }
            throw std::runtime_error("Entity not found");
        }
        EntityIndex Collection::get_entity_index(EntityId id) {
            auto it = m_registry.find(id);
            return it->second;
        }
    } // entity
} // bnjkit
