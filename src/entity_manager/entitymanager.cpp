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
            IEntity::set_logger(m_logger);
            m_logger->info("Constructor of EntityManager");
        }
        EntityManager::~EntityManager() {
            m_logger->info("Destructor of EntityManager");
        }
        std::vector<std::reference_wrapper<EntityCollection> >
        EntityManager::get_all_collections() {
            {
                std::vector<std::reference_wrapper<EntityCollection> > collections;
                collections.reserve(m_collections.size());

                for (auto& [type, collection]: m_collections) {
                    collections.emplace_back(collection->get_collection());
                }
                return collections;
            }
        }
    } // entity
} // bnjkit
