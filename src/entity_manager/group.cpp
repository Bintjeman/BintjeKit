/*!
 * @author bintjeman
 * @date 01.07.25
 * @name group.cpp
 */
#include "bintjekit/entity/group.hpp"

namespace bnjkit {
    namespace entity {
        IGroup::IGroup() {
        }
        IGroup::~IGroup() {
        }
        void IGroup::add_entity(const EntityPtr& entity) {
            auto index = m_group.entities.size();
            m_group.entities.push_back(std::move(entity));
            m_registry.emplace(entity->id(), index);
        }
        void IGroup::remove_entity(EntityPtr entity) {
            auto id = entity->id();
            auto it = m_registry.find(id);
            if (it != m_registry.end()) {
                m_group.entities[it->second] = std::move(m_group.entities.back());
                m_group.entities.pop_back();
                m_registry.erase(id);
            }
        }
        void IGroup::clear() {
        }
        SecondaryGroup& IGroup::get_groupe() {
            return m_group;
        }
        EntityRegystry& IGroup::get_registry() {
            return m_registry;
        }
        std::weak_ptr<Entity> IGroup::get_entity(EntityId id) {
            auto it = m_registry.find(id);
            if (it != m_registry.end()) {
                return m_group.entities[it->second];
            }
            throw std::runtime_error("Entity not found");
        }
        EntityIndex IGroup::get_entity_index(EntityId id) {
            return m_registry.find(id)->second;
        }
    } // entity
} // bnjkit
