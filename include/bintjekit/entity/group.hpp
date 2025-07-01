/*!
 * @author bintjeman
 * @date 26.06.25
 * @name collection.hpp
 */

#ifndef BINTJKEKIT_ENTITY_GROUP_HPP
#define BINTJKEKIT_ENTITY_GROUP_HPP
#pragma once
#include <optional>
#include "entity_helper.hpp"

namespace bnjkit {
    namespace entity {
        template<typename T>
        using TypedSecondaryGroup = std::vector<std::shared_ptr<T> >;
        class IGroup {
        public:
            IGroup();
            virtual ~IGroup();
            virtual void add_entity(const EntityPtr& entity);
            virtual void remove_entity(EntityPtr entity);
            virtual void clear();
            SecondaryGroup& get_groupe();
            virtual EntityRegystry& get_registry();
            virtual std::weak_ptr<Entity> get_entity(EntityId id);
            virtual EntityIndex get_entity_index(EntityId id);
            virtual std::optional<EntityIndex> get_entity_index_opt(EntityId id) {
                auto it = m_registry.find(id);
                return (it != m_registry.end())
                           ? std::optional(it->second)
                           : std::nullopt;
            }

        protected:
            SecondaryGroup m_group;
            EntityRegystry m_registry;
        }; // IGRoup
        template<typename EntityTypeParent>
        class HeterogeneousGroup : public IGroup {
        public:
            void add_entity(const EntityPtr& entity) override {
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
            TypedSecondaryGroup<T>& get_collection() {
                return reinterpret_cast<TypedSecondaryGroup<T>&>(m_group);
            }
        };
        // Group homogène : accepte uniquement EntityType
        template<typename EntityType>
        class HomogeneousGroup : public IGroup {
        public:
            void add_entity(const EntityPtr& entity) override {
                if (std::dynamic_pointer_cast<EntityType>(entity)) {
                    IGroup::add_entity(entity);
                } else {
                    throw std::invalid_argument("Entity type mismatch");
                }
            }
            std::shared_ptr<EntityType> get(EntityId id) {
                if (auto entity = get_entity(id)) {
                    return std::static_pointer_cast<EntityType>(entity);
                }
                return nullptr;
            }
            TypedSecondaryGroup<EntityType>& get_collection() {
                return reinterpret_cast<TypedSecondaryGroup<EntityType>&>(m_group);
            }
        };
    } // entity
} // bnjkit

#endif // BINTJKEKIT_ENTITY_GROUP_HPP
