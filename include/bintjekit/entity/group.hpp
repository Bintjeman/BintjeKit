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

        template<typename EntityTypeParent>
        class HeterogeneousGroup : public IGroup {
        }; // HeterogeneousGroup
        template<typename EntityType>
        class HomogeneousGroup : public IGroup {
        }; // HomogeneousGroup
    } // entity
} // bnjkit

#endif // BINTJKEKIT_ENTITY_COLLECTION_HPP
