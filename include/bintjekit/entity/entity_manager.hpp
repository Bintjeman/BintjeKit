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
        void create_collection();

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        TypedCollection<EntityType>& get_collection();

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        const TypedCollection<EntityType>& get_collection() const;

        template<typename... EntityTypes>
            requires (std::is_base_of_v<IEntity, EntityTypes> && ...)
        std::tuple<std::reference_wrapper<TypedCollection<EntityTypes> >...> get_collections();

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        void add(const std::shared_ptr<EntityType>& entity);

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        std::shared_ptr<EntityType> create();

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        auto get(EntityId id);

        void remove(EntityId id);
        void clear();
        std::size_t size() const;

    private:
        std::unordered_map<std::type_index, std::unique_ptr<ITypedCollection> > m_collections;
        std::unordered_map<EntityId, std::type_index> m_entity_types;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#include "bintjekit/entity/entity_manager.inl"
#endif //ENTITY_MANAGER_HPP
