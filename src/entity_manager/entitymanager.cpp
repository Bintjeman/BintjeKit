/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entitymanager.cpp
 */
#include "bintjekit/entity/entitymanager.hpp"
#include "bintjekit/logger.hpp"

namespace bnjkit {
    namespace entity {
        EntityManager::EntityManager() {
            m_logger = core::Logger::get_logger(core::module_names::ENTITY);
            m_logger->info("Constructor of EntityManager");
        }
        EntityManager::~EntityManager() {
            m_logger->info("Destructor of EntityManager");
        }
        EntityRef EntityManager::create_entity() {
            Entity entity;
            m_collection.add_entity(std::move(entity));
            return m_collection.get_entity(entity.id());
        }
        void EntityManager::add(Entity entity) {
            m_collection.add_entity(std::move(entity));
        }
        void EntityManager::remove(Entity entity) {
            m_collection.remove_entity(entity);
        }
        EntityCollection& EntityManager::get_collection() {
            return m_collection.get_collection();
        }
        const EntityCollection& EntityManager::get_collection() const {
            return m_collection.get_collection();
        }
    } // entity
} // bnjkit
