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
#include "entity_helper.hpp"

namespace bnjkit {
    namespace entity {
        template<typename T>
        using TypedEntityCollection = std::vector<T>;
        class Collection {
        public:
            Collection();
            virtual ~Collection();
            virtual void add_entity(Entity&& entity);
            virtual void remove_entity(EntityRef entity);
            virtual void remove_entity(const EntityPtr& entity);
            virtual void remove_entity(EntityId id);
            virtual void clear();
            virtual EntityCollection& get_collection();
            virtual const EntityCollection& get_collection() const;
            virtual EntityRegystry& get_registry();
            virtual EntityRef get_entity(EntityId id);
            virtual EntityIndex get_entity_index(EntityId id);
            virtual std::optional<EntityIndex> get_entity_index_opt(EntityId id) {
                auto it = m_registry.find(id);
                return (it != m_registry.end())
                           ? std::optional(it->second)
                           : std::nullopt;
            }
            template<typename T>
            TypedEntityCollection<T>& get_typed_collection() {
                return reinterpret_cast<TypedEntityCollection<T>&>(m_collection);
            }

        protected:
            EntityCollection m_collection;
            EntityRegystry m_registry;
        }; // ICollection
        template<typename EntityTypeParent>
        class HeterogeneousGroup : public Collection {
        public:
            void add_entity(Entity&& entity) override {
                if (auto derived = std::dynamic_pointer_cast<EntityTypeParent>(entity)) {
                    Collection::add_entity(std::move(entity));
                } else {
                    throw std::invalid_argument("Entity type mismatch");
                }
            }
            std::reference_wrapper<EntityTypeParent> get(EntityId id) {
                return get_entity(id);
            }
            template<typename T = EntityTypeParent>
            TypedEntityCollection<T>& get_collection() {
                return reinterpret_cast<TypedEntityCollection<T>&>(m_collection);
            }
        };
        // Group homogène : accepte uniquement EntityType
        template<typename EntityType>
        class HomogeneousGroup : public Collection {
        public:
            void add_entity(Entity&& entity) override {
                if (std::dynamic_pointer_cast<EntityType>(entity)) {
                    Collection::add_entity(std::move(entity));
                } else {
                    throw std::invalid_argument("Entity type mismatch");
                }
            }
            std::shared_ptr<EntityType> get(EntityId id) {
                return get_entity(id);
            }
            TypedEntityCollection<EntityType>& get_collection() {
                return reinterpret_cast<TypedEntityCollection<EntityType>&>(m_collection);
            }
        };
    } // entity
} // bnjkit
#endif // BINTJEKIT_ENTITY_COLLECTION_HPP
