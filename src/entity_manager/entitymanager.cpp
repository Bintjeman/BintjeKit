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
        std::shared_ptr<IEntity> EntityManager::get_entity(EntityId id) {
            auto it = m_global_registry.find(id);
            if (it == m_global_registry.end()) {
                m_logger->error("Entity not found");
                throw std::runtime_error("Entity not found");
            }
            if (auto entity = it->second.second.lock()) {
                return entity;
            }
            // Si le weak_ptr est expiré, nettoyer le registre
            m_global_registry.erase(it);
            m_logger->error("Entity expired");
            throw std::runtime_error("Entity expired");
        }
        void EntityManager::remove_entity(EntityId id) {
            auto it = m_global_registry.find(id);
            if (it != m_global_registry.end()) {
                auto& [typeIndex, weakPtr] = it->second;
                if (auto collection = m_collections.find(typeIndex);
                    collection != m_collections.end()) {
                    collection->second->remove_entity(id);
                }
                m_global_registry.erase(it);
            }
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
        void EntityManager::clear() {
            m_global_registry.clear();
            m_collections.clear();
            m_custom_groups.clear();
        }
        CustomGroup& EntityManager::create_group(const CustomGroup::GroupId& groupId) {
            return m_custom_groups.emplace(
                groupId,
                CustomGroup(* this, groupId)
            ).first->second;
        }
        CustomGroup* EntityManager::get_group(const CustomGroup::GroupId& groupId) {
            auto it = m_custom_groups.find(groupId);
            return it != m_custom_groups.end() ? & it->second : nullptr;
        }
    } // entity
} // bnjkit
