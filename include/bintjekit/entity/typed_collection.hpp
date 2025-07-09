/*!
 * @author bintjeman
 * @date 08.07.25
 * @name TypedCollection.hpp
 */

#ifndef BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
#define BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
#pragma once
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    class ITypedCollection {
    public:
        ITypedCollection();
        virtual ~ITypedCollection();
        [[nodiscard]] virtual std::size_t size() const;

    private:
    };
    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    class TypedCollection : public ITypedCollection {
    public:
        using EntityPtr = std::shared_ptr<EntityType>;
        void add(const EntityPtr& entity);
        EntityPtr create();
        void remove(EntityId id);
        EntityPtr get(EntityId id) const;
        std::vector<EntityPtr>& entities();
        const std::vector<EntityPtr>& entities() const;
        const std::unordered_map<EntityId, std::size_t>& registry() const;
        std::size_t size() const override;

    private:
        std::vector<std::shared_ptr<EntityType> > m_entities;
        std::unordered_map<unsigned long, std::size_t> m_registry;
    };
}

#include "bintjekit/entity/typed_collection.inl"
#endif // BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
