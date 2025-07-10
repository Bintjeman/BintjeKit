/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component_register.hpp
 */

#ifndef COMPONENT_REGISTER_HPP
#define COMPONENT_REGISTER_HPP
#pragma once
#include <unordered_map>
#include "bintjekit/entity/component.hpp"
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    class IComponentRegistry {
    public:
        virtual ~IComponentRegistry() = default;
    };

    template<typename ComponentType>
        requires is_component<ComponentType>
    class ComponentRegistry : public IComponentRegistry {
    public:
        void add(EntityId entity_id, ComponentType component);

        ComponentType* get(EntityId entity_id);
        const ComponentType* get(EntityId entity_id) const;

        [[nodiscard]] bool has(EntityId entity_id) const;

        void remove(EntityId entity_id);

    private:
        std::unordered_map<EntityId, ComponentType> m_components;
    };
}

#include "bintjekit/entity/component_register.inl"
#endif //COMPONENT_REGISTER_HPP
