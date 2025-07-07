/*!
 * @author bintjeman
 * @date 01.07.25
 * @name Collection.hpp
 */

#ifndef  BINTJEKIT_ENTITY_COLLECTION_HPP
#define  BINTJEKIT_ENTITY_COLLECTION_HPP
#pragma once
#include <vector>
#include <memory>
#include <optional>
#include <spdlog/spdlog.h>
#include "entity_helper.hpp"

namespace bnjkit::entity {
    template<typename T>
    using TypedEntityCollection = std::vector<T>;
    class Collection {
    public:
        Collection();
        ~Collection();
        void add_entity(const std::shared_ptr<IEntity>& entity);
        void remove_entity(const EntityPtr& entity);
        void remove_entity(EntityId id);
        void clear();
        EntityCollection& get_collection();
        const EntityCollection& get_collection() const;
        EntityRegystry& get_registry();
        std::shared_ptr<IEntity> get_entity(EntityId id);
        EntityIndex get_entity_index(EntityId id);
        std::optional<EntityIndex> get_entity_index_opt(EntityId id) {
            auto it = m_registry.find(id);
            return it != m_registry.end()
                       ? std::optional(it->second)
                       : std::nullopt;
        }
        std::size_t size() const;
        template<typename T>
        TypedEntityCollection<T>& get_typed_collection() {
            return reinterpret_cast<TypedEntityCollection<T>&>(m_collection);
        }
        template<typename T>
        bool is_valid_type(const std::shared_ptr<IEntity>& entity) const {
            return std::dynamic_pointer_cast<T>(entity) != nullptr;
        }

    protected:
        EntityCollection m_collection;
        EntityRegystry m_registry;
        std::shared_ptr<spdlog::logger> m_logger;
    }; // ICollection
    // template<typename EntityTypeParent>
    // class HeterogeneousGroup : public Collection {
    // public:
    //     void add_entity(const std::shared_ptr<IEntity>& entity) override {
    //         if (!entity || !entity->valid()) {
    //             m_logger->warn("Cannot add invalid entity");
    //             throw std::invalid_argument("Cannot add invalid entity");
    //         }
    //         if (auto derived[[maybe_unused]] = std::dynamic_pointer_cast<EntityTypeParent>(entity)) {
    //             Collection::add_entity(entity);
    //         } else {
    //             m_logger->warn("Entity type mismatch");
    //             throw std::invalid_argument("Entity type mismatch");
    //         }
    //     }
    //     std::shared_ptr<EntityTypeParent> get(EntityId id) {
    //         return get_entity(id);
    //     }
    //     template<typename T = EntityTypeParent>
    //     TypedEntityCollection<T>& get_collection() {
    //         return reinterpret_cast<TypedEntityCollection<T>&>(m_collection);
    //     }
    // };
    // Group homogène : accepte uniquement EntityType
    // template<typename EntityType>
    // class HomogeneousGroup : public Collection {
    // public:
    //     void add_entity(const std::shared_ptr<IEntity>& entity) override {
    //         if (!entity || !entity->valid()) {
    //             m_logger->warn("Cannot add invalid entity");
    //             throw std::invalid_argument("Cannot add invalid entity");
    //         }
    //         if (std::dynamic_pointer_cast<EntityType>(entity)) {
    //             Collection::add_entity(entity);
    //         } else {
    //             m_logger->warn("Entity type mismatch");
    //             throw std::invalid_argument("Entity type mismatch");
    //         }
    //     }
    //     std::shared_ptr<EntityType> get(EntityId id) {
    //         return get_entity(id);
    //     }
    // };
}
#endif // BINTJEKIT_ENTITY_COLLECTION_HPP
