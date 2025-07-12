/*!
 * @author bintjeman
 * @date 08.07.25
 * @name TypedCollection.hpp
 */

#ifndef BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
#define BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
#pragma once
#include <memory>
#include <vector>
#include <functional>
// #include <unordered_map>
#include "bintjekit/entity/ientity.hpp"
// #include "bintjekit/entity/components/component_view.hpp"
// #include "bintjekit/entity/fwd.hpp"
#include "bintjekit/entity/entity_collection.hpp"

namespace bnjkit::entity {
    template<typename T>
    class ComponentView;

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    class TypedCollection final : public EntityCollection {
    public:
        using EntityPtr = std::shared_ptr<EntityType>;
        using BasePtr = EntityCollection::EntityPtr;
        template<typename T = EntityType>
            requires (!std::is_same_v<T, IEntity>)
        void add(const std::shared_ptr<T>& entity);

        void add(const BasePtr& entity) override;
        EntityPtr create();

        EntityPtr get_typed(const EntityId id) const {
            return std::dynamic_pointer_cast<EntityType>(EntityCollection::get(id));
        }

        BasePtr get(const EntityId id) const override {
            return EntityCollection::get(id);
        }

        std::vector<std::shared_ptr<EntityType> >& typed_entities() {
            return reinterpret_cast<std::vector<std::shared_ptr<EntityType> >&>(m_entities);
        }

        const std::vector<std::shared_ptr<EntityType> >& typed_entities() const {
            return reinterpret_cast<const std::vector<std::shared_ptr<EntityType> >&>(m_entities);
        }
        ComponentView<EntityType> create_typed_view() const {
            return ComponentView<EntityType>(* this, [](const std::shared_ptr<EntityType>&) { return true; });
        }

        void remove(EntityId id) override;

        using EntityCollection::entities;
        using EntityCollection::registry;
        using EntityCollection::size;
        using EntityCollection::create_view;

    protected:
        using EntityCollection::m_entities;
        using EntityCollection::m_registry;
    };
}

#include "bintjekit/entity/typed_collection.inl"
#endif // BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
