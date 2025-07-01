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
            std::shared_ptr<Entity> create_entity();
            std::shared_ptr<Entity> get_entity(EntityId id);
            void remove(std::shared_ptr<Entity> entity);
            [[nodiscard]] EntityCollection& get_collection();
            [[nodiscard]] const EntityCollection& get_collection() const ;
            void clear();

        private:
            std::shared_ptr<spdlog::logger> m_logger;
            Collection m_collection;
        };
    } // entity
} // bnjkit

#endif // BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
