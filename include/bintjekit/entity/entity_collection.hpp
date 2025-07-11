/*!
 * @author bintjeman
 * @date 08.07.25
 * @name entity_collection.hpp
 */

#ifndef ENTITY_COLLECTION_HPP
#define ENTITY_COLLECTION_HPP
#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>
#include "bintjekit/entity/fwd.hpp"
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    class EntityCollection {
    public:
        using EntityPtr = std::shared_ptr<IEntity>;

        class ViewBuilder {
        public:
            explicit ViewBuilder(const EntityCollection& collection);
            ViewBuilder& where(std::function<bool(const EntityPtr&)> filter);
            ComponentView<IEntity> build();

        private:
            const EntityCollection& m_collection;
            std::function<bool(const EntityPtr&)> m_filter = [](const EntityPtr&) { return true; };
        };

        virtual ~EntityCollection() = default;
        virtual void add(const EntityPtr& entity);
        virtual void remove(EntityId id);
        virtual EntityPtr get(EntityId id) const;
        virtual void clear();
        virtual std::vector<EntityPtr>& entities() { return m_entities; }
        virtual const std::vector<EntityPtr>& entities() const { return m_entities; }
        virtual const std::unordered_map<EntityId, std::size_t>& registry() const { return m_registry; }
        [[nodiscard]] virtual std::size_t size() const { return m_entities.size(); }
        virtual ViewBuilder create_view() const { return ViewBuilder(* this); }

    protected:
        std::vector<EntityPtr> m_entities;
        std::unordered_map<EntityId, std::size_t> m_registry;
    };
}

#endif //ENTITY_COLLECTION_HPP
