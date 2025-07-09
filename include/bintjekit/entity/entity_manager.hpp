/*!
 * @author bintjeman
 * @date 08.07.25
 * @name entity_manager.hpp
 */

#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP
#pragma once
#include <typeindex>
#include <unordered_map>
#include "bintjekit/entity/typed_collection.hpp"
#include "bintjekit/logger/logger.hpp"

namespace bnjkit::entity {
    class EntityManager {
    public:
        EntityManager();
        ~EntityManager();

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        void create_collection() {
            if (!m_collections.contains(std::type_index(typeid(EntityType)))) {
                auto type_index = std::type_index(typeid(EntityType));
                m_collections.emplace(type_index,
                                      std::make_unique<TypedCollection<EntityType> >());
            } else {
                m_logger->warn("Collection {} already exists", typeid(EntityType).name());
            }
        }
        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        TypedCollection<EntityType>& get_collection() {
            auto type_index = std::type_index(typeid(EntityType));
            auto it = m_collections.find(type_index);
            if (it == m_collections.end()) {
                m_logger->warn("Collection {} does not exist", type_index.name());
                create_collection<EntityType>();
                it = m_collections.find(type_index);
            }
            return * static_cast<TypedCollection<EntityType>*>(it->second.get());
        }
        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        const TypedCollection<EntityType>& get_collection() const {
            auto type_index = std::type_index(typeid(EntityType));
            auto it = m_collections.find(type_index);
            if (it == m_collections.end()) {
                m_logger->warn("Collection {} does not exist", type_index.name());
                throw std::runtime_error("Collection does not exist");
            }
            return * static_cast<TypedCollection<EntityType>*>(it->second.get());
        }
        template<typename... EntityTypes>
            requires (std::is_base_of_v<IEntity, EntityTypes> && ...)
        auto get() {
            return std::tuple<std::reference_wrapper<TypedCollection<EntityTypes> >...>(
                get_collection<EntityTypes>()...
            );
        }
        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        void add(const std::shared_ptr<EntityType>& entity) {
            static_assert(!std::is_void<EntityType>::value, "EntityType must be a complete type");
            auto& collection = get_collection<EntityType>();
            auto type_index = std::type_index(typeid(EntityType));
            m_entity_types[entity->id()] = type_index;
            collection.add(entity);
        }
        template<typename EntytyType=IEntity>
            requires std::is_base_of_v<IEntity, EntytyType>
        std::shared_ptr<EntytyType> create() {
            auto entity = std::make_shared<EntytyType>();
            add(entity);
            return entity;
        }
        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        auto get(EntityId id) {
            if (m_entity_types.contains(id)) {
                auto entity_type = m_entity_types.find(id)->second;
                if (m_collections.contains(entity_type)) {
                    auto& collection = * static_cast<TypedCollection<EntityType>*>(m_collections.at(entity_type)
                        .get());
                    return collection.get(id);
                }
                m_logger->warn("Collection {} does not exist", entity_type.name());
            }
            m_logger->warn("Entity {} does not exist", id);
        }
        void remove(EntityId id) {
            if (m_entity_types.contains(id)) {
                auto entity_type = m_entity_types.find(id)->second;
                if (m_collections.contains(entity_type)) {
                    auto& collection = * static_cast<TypedCollection<IEntity>*>(m_collections.at(entity_type)
                        .get());
                    collection.remove(id);
                }
                m_logger->warn("Collection {} does not exist", entity_type.name());
            }
            m_logger->warn("Entity {} does not exist", id);
        }
        void clear();
        std::size_t size() const;

    private:
        std::unordered_map<std::type_index, std::unique_ptr<ITypedCollection> > m_collections;
        std::unordered_map<EntityId, std::type_index> m_entity_types;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}

#endif //ENTITY_MANAGER_HPP
