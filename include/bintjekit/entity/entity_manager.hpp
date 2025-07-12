/*!
 * @author bintjeman
 * @date 08.07.25
 * @name entity_manager.hpp
 */
#ifndef BNJKIT_ENTITY_ENTITY_MANAGER_HPP
#define BNJKIT_ENTITY_ENTITY_MANAGER_HPP
#pragma once
#include <typeindex>
#include <unordered_map>
#include <utility>
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/entity/typed_collection.hpp"
#include "components/component_register.hpp"

namespace bnjkit::entity {
    class EntityManager {
    public:
        EntityManager();
        virtual ~EntityManager();

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

        template<typename... EntityTypes>
            requires (std::is_base_of_v<IEntity, EntityTypes> && ...)
        std::tuple<std::reference_wrapper<TypedCollection<EntityTypes> >...> get_collections() const;

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        void add(const std::shared_ptr<EntityType>& entity);

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        std::shared_ptr<EntityType> create();

        template<typename EntityType=IEntity>
            requires std::is_base_of_v<IEntity, EntityType>
        auto get(EntityId id);

        void mark_for_removal(EntityId id);
        void process_pending_removals();
        void clear();
        std::size_t size() const;
        template<typename ComponentType>
            requires is_component<ComponentType>
        void register_component();
        template<typename ComponentType>
            requires is_component<ComponentType>
        void add_component(EntityId entity_id, ComponentType component);
        template<typename ComponentType>
            requires is_component<ComponentType>
        ComponentType* get_component(EntityId entity_id);
        template<typename ComponentType>
            requires is_component<ComponentType>
        const ComponentType* get_component(EntityId entity_id) const;
        template<typename ComponentType>
            requires is_component<ComponentType>
        bool has_component(EntityId entity_id) const;
        template<typename ComponentType>
        ComponentRegistry<ComponentType>& get_component_registry();
        template<typename ComponentType>
        const ComponentRegistry<ComponentType>& get_component_registry() const;
        template<typename ComponentType>
        ComponentView<ComponentType>& create_view();
        template<typename ComponentType>
        const ComponentView<ComponentType>& create_view() const;

    protected:
        void remove(EntityId id);

        std::unordered_map<std::type_index, std::unique_ptr<IComponentRegistry>> m_component_registries;
        std::unordered_map<std::type_index, std::unique_ptr<EntityCollection>> m_collections;
        std::unordered_map<EntityId, std::type_index> m_entity_types;

        std::vector<EntityId> m_pending_removals;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#include "bintjekit/entity/entity_manager.inl"
#endif // BNJKIT_ENTITY_ENTITY_MANAGER_HPP
