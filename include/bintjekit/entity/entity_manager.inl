/*!
 * @author bintjeman
 * @date 09.07.25
 * @name entity_manager.inl
 */

#ifndef BINTJEKIT_ENTITY_ENTITY_MANAGER_INL
#define BINTJEKIT_ENTITY_ENTITY_MANAGER_INL
#pragma once
#include <type_traits>
#include "entity_manager.hpp"
#include "bintjekit/entity/ientity.hpp"
#include "components/i_component_builder.hpp"

namespace bnjkit::entity {
    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    void EntityManager::create_collection() {
        if (!m_collections.contains(std::type_index(typeid(EntityType)))) {
            auto type_index = std::type_index(typeid(EntityType));
            m_collections.emplace(type_index,
                                  std::make_unique<TypedCollection<EntityType> >());
        } else {
            m_logger->warn("Collection {} already exists", typeid(EntityType).name());
        }
    }

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    TypedCollection<EntityType>& EntityManager::get_collection() {
        const auto type_index = std::type_index(typeid(EntityType));
        auto it = m_collections.find(type_index);
        if (it == m_collections.end()) {
            m_logger->warn("Collection {} does not exist", type_index.name());
            create_collection<EntityType>();
            it = m_collections.find(type_index);
        }
        return * static_cast<TypedCollection<EntityType>*>(it->second.get());
    }

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    const TypedCollection<EntityType>& EntityManager::get_collection() const {
        const auto type_index = std::type_index(typeid(EntityType));
        const auto it = m_collections.find(type_index);
        if (it == m_collections.end()) {
            m_logger->warn("Collection {} does not exist", type_index.name());
            throw std::runtime_error("Collection does not exist");
        }
        return * static_cast<TypedCollection<EntityType>*>(it->second.get());
    }

    template<typename... EntityTypes>
        requires (std::is_base_of_v<IEntity, EntityTypes> && ...)
    std::tuple<std::reference_wrapper<TypedCollection<EntityTypes> >...>
    EntityManager::get_collections() {
        return std::tuple<std::reference_wrapper<TypedCollection<EntityTypes> >...>(
            get_collection<EntityTypes>()...
        );
    }

    template<typename... EntityTypes>
        requires (std::is_base_of_v<IEntity, EntityTypes> && ...)
    std::tuple<std::reference_wrapper<TypedCollection<EntityTypes> >...>
    EntityManager::get_collections() const {
        return std::make_tuple(std::reference_wrapper<TypedCollection<EntityTypes> >(
            const_cast<TypedCollection<EntityTypes>&>(get_collection<EntityTypes>()))...);
    }

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    void EntityManager::add(const std::shared_ptr<EntityType>& entity) {
        static_assert(!std::is_void_v<EntityType>, "EntityType must be a complete type");
        auto& collection = get_collection<EntityType>();
        auto type_index = std::type_index(typeid(EntityType));
        m_entity_types.emplace(entity->id(), type_index);
        collection.add(entity);
    }

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    std::shared_ptr<EntityType> EntityManager::create() {
        auto entity = std::make_shared<EntityType>();
        if (const auto it = m_builders.find(typeid(EntityType)); it != m_builders.end()) {
            it->second->build(*entity);
        }
        add(entity);
        return entity;
    }
    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    auto EntityManager::get(EntityId id) {
        if (m_entity_types.contains(id)) {
            const auto entity_type = m_entity_types.find(id)->second;
            if (m_collections.contains(entity_type)) {
                auto& collection = * static_cast<TypedCollection<EntityType>*>(m_collections.at(entity_type)
                    .get());
                return collection.get(id);
            }
            m_logger->warn("Collection {} does not exist", entity_type.name());
        }
        m_logger->warn("Entity {} does not exist", id);
    }
    template<typename ComponentType> requires is_component<ComponentType>
    void EntityManager::register_component() {
        if (auto type_index = std::type_index(typeid(ComponentType)); !m_component_registries.contains(type_index)) {
            m_component_registries.emplace(
                type_index,
                std::make_unique<ComponentRegistry<ComponentType> >()
            );
        }
    }
    template<typename ComponentType> requires is_component<ComponentType>
    ComponentType& EntityManager::add_component(EntityId entity_id, ComponentType component) {
        return get_component_registry<ComponentType>().add(entity_id, std::move(component));
    }
    template<typename ComponentType> requires is_component<ComponentType>
    ComponentType& EntityManager::add_component(EntityId entity_id) {
        return get_component_registry<ComponentType>().add(entity_id);
    }
    template<typename ComponentType> requires is_component<ComponentType>
    ComponentType* EntityManager::get_component(EntityId entity_id) {
        return get_component_registry<ComponentType>().get(entity_id);
    }
    template<typename ComponentType> requires is_component<ComponentType>
    const ComponentType* EntityManager::get_component(EntityId entity_id) const {
        return get_component_registry<ComponentType>().get(entity_id);
    }
    template<typename ComponentType> requires is_component<ComponentType>
    bool EntityManager::has_component(EntityId entity_id) const {
        return get_component_registry<ComponentType>().has(entity_id);
    }

    template<typename ComponentType>
    ComponentRegistry<ComponentType>& EntityManager::get_component_registry() {
        auto type_index = std::type_index(typeid(ComponentType));
        const auto it = m_component_registries.find(type_index);
        if (it == m_component_registries.end()) {
            auto [inserted_it, _] = m_component_registries.emplace(
                type_index,
                std::make_unique<ComponentRegistry<ComponentType> >()
            );
            return * static_cast<ComponentRegistry<ComponentType>*>(
                inserted_it->second.get()
            );
        }
        return * static_cast<ComponentRegistry<ComponentType>*>(
            it->second.get()
        );
    }
    template<typename ComponentType>
    const ComponentRegistry<ComponentType>& EntityManager::get_component_registry() const {
        const auto type_index = std::type_index(typeid(ComponentType));
        const auto it = m_component_registries.find(type_index);
        if (it == m_component_registries.end()) {
            throw std::runtime_error("Component registry does not exist");
        }
        return * static_cast<ComponentRegistry<ComponentType>*>(
            it->second.get()
        );
    }
    template<typename ComponentType>
    ComponentView<ComponentType>& EntityManager::create_view() {
        return get_component_registry<ComponentType>().create_view();
    }
    template<typename ComponentType>
    const ComponentView<ComponentType>& EntityManager::create_view() const {
        return get_component_registry<ComponentType>().create_view();
    }
    template<typename EntityType>
    void EntityManager::register_builder(std::unique_ptr<IComponentBuilder> builder) {
        m_builders[typeid(EntityType)] = std::move(builder);
    }

    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    std::shared_ptr<EntityType> EntityManager::create_entity() {
        auto entity = std::make_shared<EntityType>();
        add(entity);
        return entity;
    }
}
#endif // BINTJEKIT_ENTITY_ENTITY_MANAGER_INL
