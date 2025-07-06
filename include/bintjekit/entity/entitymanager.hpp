/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entitymanager.hpp
 */

#ifndef BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#define BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#pragma once
#include <memory>
#include <typeindex>
#include <spdlog/fwd.h>
#include "bintjekit/entity/collection.hpp"
#include "bintjekit/entity/customgroup.hpp"

namespace bnjkit {
    namespace entity {
        class EntityManager {
        public:
            template<typename T>
            void register_entity_type() {
                auto typeIndex = std::type_index(typeid(T));
                if (!m_collections.contains(typeIndex)) {
                    m_collections[typeIndex] = std::make_unique<HomogeneousGroup<T> >();
                }
            }
            EntityManager();
            ~EntityManager();
            template<typename EntityType>
            void add_entity(std::shared_ptr<EntityType> entity) {
                if (!entity || !entity->valid()) {
                    m_logger->error("Entity is invalid");
                    throw std::invalid_argument("Entity is invalid");
                }
                auto typeIndex = std::type_index(typeid(EntityType));
                if (!m_collections.contains(typeIndex)) {
                    m_collections[typeIndex] = std::make_unique<HomogeneousGroup<EntityType> >();
                }
                m_collections[typeIndex]->add_entity(entity);
                m_globalRegistry[entity->id()] = std::make_pair(typeIndex, entity);
            }
            std::shared_ptr<IEntity> get_entity(EntityId id) {
                auto it = m_globalRegistry.find(id);
                if (it == m_globalRegistry.end()) {
                    m_logger->error("Entity not found");
                    throw std::runtime_error("Entity not found");
                }
                if (auto entity = it->second.second.lock()) {
                    return entity;
                }
                // Si le weak_ptr est expiré, nettoyer le registre
                m_globalRegistry.erase(it);
                m_logger->error("Entity expired");
                throw std::runtime_error("Entity expired");
            }
            template<typename T>
            std::shared_ptr<T> get(EntityId id) {
                auto baseEntity = get_entity(id);
                auto result = std::dynamic_pointer_cast<T>(baseEntity);
                if (!result) {
                    m_logger->error("Incorrect entity type");
                    throw std::runtime_error("Incorrect entity type");
                }
                return result;
            }
            void remove_entity(EntityId id) {
                auto it = m_globalRegistry.find(id);
                if (it != m_globalRegistry.end()) {
                    auto& [typeIndex, weakPtr] = it->second;
                    if (auto collection = m_collections.find(typeIndex);
                        collection != m_collections.end()) {
                        collection->second->remove_entity(id);
                    }
                    m_globalRegistry.erase(it);
                }
            }
            std::vector<std::reference_wrapper<EntityCollection> > get_all_collections();
            template<typename... Types>
            std::tuple<std::reference_wrapper<TypedEntityCollection<Types> >...>
            get_typed_collections() {
                return std::make_tuple(
                    std::ref(m_collections[std::type_index(typeid(Types))]
                        ->template get_typed_collection<Types>())...
                );
            }
            CustomGroup& create_group(const CustomGroup::GroupId& groupId) {
                return m_customGroups.emplace(
                    groupId,
                    CustomGroup(* this, groupId)
                ).first->second;
            }
            CustomGroup* get_group(const CustomGroup::GroupId& groupId) {
                auto it = m_customGroups.find(groupId);
                return it != m_customGroups.end() ? & it->second : nullptr;
            }

        private:
            std::unordered_map<std::type_index, std::unique_ptr<Collection> > m_collections;
            std::unordered_map<EntityId, std::pair<std::type_index, std::weak_ptr<IEntity> > >
            m_globalRegistry;
            std::unordered_map<CustomGroup::GroupId, CustomGroup> m_customGroups;
            std::shared_ptr<spdlog::logger> m_logger;
            Collection m_collection;
        };
    } // entity
} // bnjkit
#include "customgroup.inl"

#endif // BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
