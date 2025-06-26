/*!
 * @author bintjeman
 * @date 26.06.25
 * @name collection.hpp
 */

#ifndef BINTJKEKIT_ENTITY_COLLECTION_HPP
#define BINTJKEKIT_ENTITY_COLLECTION_HPP
#pragma once
#include <optional>
#include "entity_helper.hpp"

namespace bnjkit {
    namespace entity {
        class IGroup {
        public:
            IGroup();
            virtual ~IGroup();
            virtual void add_entity(EntityPtr entity);
            virtual void remove_entity(EntityPtr entity);
            virtual void clear();
            virtual EntityCollection& get_collection();
            virtual EntityRegystry& get_registry();
            virtual EntityPtr get_entity(EntityId id);
            virtual EntityIndex get_entity_index(EntityId id);
            virtual std::optional<EntityIndex> get_entity_index_opt(EntityId id) {
                auto it = m_registry.find(id);
                return (it != m_registry.end())
                           ? std::optional<EntityIndex>(it->second)
                           : std::nullopt;
            }

        protected:
            EntityCollection m_collection;
            EntityRegystry m_registry;
        }; // IGRoup
        template<typename T>
        using TypedEntityCollection = std::vector<std::shared_ptr<T> >;
        template<typename EntityTypeParent>
        class HeterogeneousGroup : public IGroup {
        public:
            void add_entity(EntityPtr entity) override {
                // Vérifie si l'entité est du bon type ou hérite du type parent
                if (auto derived = std::dynamic_pointer_cast<EntityTypeParent>(entity)) {
                    IGroup::add_entity(entity);
                } else {
                    throw std::invalid_argument("Entity type mismatch");
                }
            }
            std::shared_ptr<EntityTypeParent> get(EntityId id) {
                if (auto entity = get_entity(id)) {
                    return std::static_pointer_cast<EntityTypeParent>(entity);
                    // On peut utiliser static_cast car on est sûr du type
                }
                return nullptr;
            }
            template<typename T = EntityTypeParent>
            TypedEntityCollection<T>& get_collection() {
                return reinterpret_cast<TypedEntityCollection<T>&>(m_collection);
            }
        };
        // Group homogène : accepte uniquement EntityType
        template<typename EntityType>
        class HomogeneousGroup : public IGroup {
        public:
            void add_entity(EntityPtr entity) override {
                // Vérifie si l'entité est exactement du type demandé
                if (std::dynamic_pointer_cast<EntityType>(entity) &&
                    typeid(* entity) == typeid(EntityType)) {
                    IGroup::add_entity(entity);
                } else {
                    throw std::invalid_argument("Entity type mismatch");
                }
            }
            std::shared_ptr<EntityType> get(EntityId id) {
                if (auto entity = get_entity(id)) {
                    return std::static_pointer_cast<EntityType>(entity);
                    // On peut utiliser static_cast car on est sûr du type
                }
                return nullptr;
            }
            TypedEntityCollection<EntityType>& get_collection() override {
                return reinterpret_cast<TypedEntityCollection<EntityType>&>(m_collection);
            }
        };
    } // entity
} // bnjkit

#endif // BINTJKEKIT_ENTITY_COLLECTION_HPP
