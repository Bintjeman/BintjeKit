/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entitymanager.hpp
 */

#ifndef BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#define BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#pragma once
#include <memory>
#include <spdlog/fwd.h>
#include "bintjekit/entity/collection.hpp"

namespace bnjkit {
    namespace entity {
        class EntityManager {
        public:
            EntityManager();
            ~EntityManager();
            void add_entity(const std::shared_ptr<Entity>& entity);
            std::shared_ptr<Entity> get_entity(EntityId id);
            void remove(const std::shared_ptr<Entity>& entity);
            [[nodiscard]] EntityCollection& get_collection();
            [[nodiscard]] const EntityCollection& get_collection() const;
            void clear();
            template<class EntityType>
            std::shared_ptr<EntityType> create_entity() {
                return std::static_pointer_cast<EntityType>(create_entity());
            }

        private:
            std::shared_ptr<Entity> create_entity();
            std::shared_ptr<spdlog::logger> m_logger;
            Collection m_collection;
        };
    } // entity
} // bnjkit

#endif // BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
