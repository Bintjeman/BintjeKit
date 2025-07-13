/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component_register.hpp
 */

#ifndef COMPONENT_REGISTER_HPP
#define COMPONENT_REGISTER_HPP
#pragma once
#include <unordered_map>
#include "component.hpp"
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    class IComponentRegistry {
    public:
        virtual ~IComponentRegistry();
        virtual void remove(EntityId entity_id) =0;
        virtual void clear() =0;
    };

    template<typename ComponentType>
        requires is_component<ComponentType>
    class ComponentRegistry final : public IComponentRegistry {
    public:
        class Iterator {
        private:
            typename std::unordered_map<EntityId, ComponentType>::const_iterator m_it;

        public:
            EntityId operator*() const { return m_it->first; }
            // ... autres méthodes d'itérateur
        };

        ComponentType& add(EntityId entity_id, ComponentType component);

        ComponentType& add(EntityId entity_id);

        ComponentType* get(EntityId entity_id);
        const ComponentType* get(EntityId entity_id) const;

        [[nodiscard]] bool has(EntityId entity_id) const;

        void remove(EntityId entity_id) override;
        void clear() override;

    private:
        std::unordered_map<EntityId, ComponentType> m_components;
    };
    Iterator begin() const { return Iterator(m_components.begin()); }
    Iterator end() const { return Iterator(m_components.end()); }

}

#include "bintjekit/entity/components/component_register.inl"
#endif //COMPONENT_REGISTER_HPP
