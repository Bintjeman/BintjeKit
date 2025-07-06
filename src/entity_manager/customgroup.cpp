/*!
 * @author bintjeman
 * @date 06.07.25
 * @name customgroup.cpp
 */
#include "bintjekit/entity/customgroup.hpp"
#include "bintjekit/entity/entitymanager.hpp"
namespace bnjkit {
namespace entity {
    CustomGroup::CustomGroup(EntityManager& manager, const GroupId& id)
    : m_entityManager(manager), m_group_id(id) {
    }
    void CustomGroup::add(EntityId entityId) {
        if (m_entityManager.get_entity(entityId)) {
            m_entity_ids.insert(entityId);
        }
    }
    void CustomGroup::remove(EntityId entityId) {
        m_entity_ids.erase(entityId);
    }
    const CustomGroup::GroupId& CustomGroup::id() const {
        return m_group_id;
    }
    size_t CustomGroup::size() const { return m_entity_ids.size(); }
    bool CustomGroup::empty() const { return m_entity_ids.empty(); }
    bool CustomGroup::contains(EntityId id) const { return m_entity_ids.count(id) > 0; }
} // entity
} // bnjkit