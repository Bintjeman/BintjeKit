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
            Entity::set_logger(m_logger);
            m_logger->info("Constructor of EntityManager");
        }
        EntityManager::~EntityManager() {
            m_logger->info("Destructor of EntityManager");
        }
        std::shared_ptr<Entity> EntityManager::create_entity() {
            std::shared_ptr<Entity> entity = std::make_shared<Entity>();
            m_collection.add_entity(entity);
            return entity;
        }
        std::shared_ptr<Entity> EntityManager::get_entity(EntityId id) {
            return m_collection.get_entity(id);
        }
        void EntityManager::remove(const std::shared_ptr<Entity> entity) {
            m_collection.remove_entity(entity);
        }
        EntityCollection& EntityManager::get_collection() {
            return m_collection.get_collection();
        }
        const EntityCollection& EntityManager::get_collection() const {
            return m_collection.get_collection();
        }
        void EntityManager::clear() {
            m_collection.clear();
        }
    } // entity
} // bnjkit
