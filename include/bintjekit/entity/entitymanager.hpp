// entitymanager.hpp
#ifndef BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#define BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#pragma once
#include <memory>
#include <typeindex>
#include "bintjekit/entity/collection.hpp"
#include "bintjekit/entity/customgroup.hpp"
namespace bnjkit {
    namespace entity {
        class EntityManager {
        public:
            EntityManager();
            ~EntityManager();
            template<typename T>
            void register_entity_type();
            template<typename EntityType>
            void add_entity(std::shared_ptr<EntityType> entity);
            std::shared_ptr<IEntity> get_entity(EntityId id);
            template<typename T>
            std::shared_ptr<T> get(EntityId id);
            void remove_entity(EntityId id);
            std::vector<std::reference_wrapper<EntityCollection>> get_all_collections();
            template<typename... Types>
            std::tuple<std::reference_wrapper<TypedEntityCollection<Types>>...>
            get_typed_collections();
            CustomGroup& create_group(const CustomGroup::GroupId& groupId);
            CustomGroup* get_group(const CustomGroup::GroupId& groupId);
        private:
            std::unordered_map<std::type_index, std::unique_ptr<Collection>> m_collections;
            std::unordered_map<EntityId, std::pair<std::type_index, std::weak_ptr<IEntity>>> m_globalRegistry;
            std::unordered_map<CustomGroup::GroupId, CustomGroup> m_customGroups;
            std::shared_ptr<spdlog::logger> m_logger;
            Collection m_collection;
        };
    }
}
#include "bintjekit/entity/entitymanager.inl"
#endif