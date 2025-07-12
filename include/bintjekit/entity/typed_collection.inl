/*!
 * @author bintjeman
 * @date 08.07.25
 * @name typed_collection.inl
 */

#ifndef BINTJEKIT_ENTITY_TYPED_COLLECTION_INL
#define BINTJEKIT_ENTITY_TYPED_COLLECTION_INL
#pragma once
// #include "bintjekit/entity/components/component_view.hpp"

namespace bnjkit::entity {
    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    template<typename T> requires (!std::is_same_v<T, IEntity>)
    void TypedCollection<EntityType>::add(const std::shared_ptr<T>& entity) {
        EntityCollection::add(std::static_pointer_cast<IEntity>(entity));
    }
    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    void TypedCollection<EntityType>::add(const BasePtr& entity) {
        if (auto typed = std::dynamic_pointer_cast<EntityType>(entity)) {
            add(typed);
        }
    }
    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    typename TypedCollection<EntityType>::EntityPtr TypedCollection<EntityType>::create() {
        auto entity = std::make_shared<EntityType>();
        add(entity);
        return entity;
    }
    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    void TypedCollection<EntityType>::remove(const EntityId id) {
        EntityCollection::remove(id);
    }


}
#endif // BINTJEKIT_ENTITY_TYPED_COLLECTION_INL
