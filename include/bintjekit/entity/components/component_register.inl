/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component_register.inl
 */

#ifndef COMPONENT_REGISTER_INL
#define COMPONENT_REGISTER_INL
#pragma once
namespace bnjkit::entity {
    template<typename ComponentType> requires is_component<ComponentType>
    void ComponentRegistry<ComponentType>::add(EntityId entity_id, ComponentType component) {
        m_components[entity_id] = std::move(component);
    }
    template<typename ComponentType> requires is_component<ComponentType>
    ComponentType* ComponentRegistry<ComponentType>::get(EntityId entity_id) {
        auto it = m_components.find(entity_id);
        return it != m_components.end() ? & it->second : nullptr;
    }
    template<typename ComponentType> requires is_component<ComponentType>
    const ComponentType* ComponentRegistry<ComponentType>::get(EntityId entity_id) const {
        auto it = m_components.find(entity_id);
        return it != m_components.end() ? & it->second : nullptr;
    }
    template<typename ComponentType> requires is_component<ComponentType>
    bool ComponentRegistry<ComponentType>::has(EntityId entity_id) const {
        return m_components.contains(entity_id);
    }
    template<typename ComponentType> requires is_component<ComponentType>
    void ComponentRegistry<ComponentType>::remove(EntityId entity_id) {
        m_components.erase(entity_id);
    }
    template<typename ComponentType> requires is_component<ComponentType>
    void ComponentRegistry<ComponentType>::clear() {
        m_components.clear();
    }
}
#endif //COMPONENT_REGISTER_INL
