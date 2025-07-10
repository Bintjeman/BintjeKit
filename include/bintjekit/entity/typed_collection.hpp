/*!
 * @author bintjeman
 * @date 08.07.25
 * @name TypedCollection.hpp
 */

#ifndef BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
#define BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
#pragma once
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    template<typename T>
    class ComponentView;

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
        class ViewBuilder {
        private:
            const TypedCollection<EntityType>& m_collection;
            std::function<bool(const EntityPtr&)> m_filter = [](const EntityPtr&) { return true; };

        public:
            explicit ViewBuilder(const TypedCollection<EntityType>& collection);
            ViewBuilder& where(std::function<bool(const EntityPtr&)> filter);
            ComponentView<EntityType> build();
        };
        void add(const EntityPtr& entity);
        EntityPtr create();
        void remove(EntityId id);
        EntityPtr get(EntityId id) const;
        std::vector<EntityPtr>& entities();
        const std::vector<EntityPtr>& entities() const;
        const std::unordered_map<EntityId, std::size_t>& registry() const;
        std::size_t size() const override;
        ViewBuilder create_view() const;

    protected:
        std::vector<std::shared_ptr<EntityType> > m_entities;
        std::unordered_map<unsigned long, std::size_t> m_registry;
    };
}

#include "bintjekit/entity/typed_collection.inl"
#endif // BINTJEKIT_ENTITY_TYPEDCOLLECTION_HPP
