/*!
 * @author bintjeman
 * @date 09.07.25
 * @name entity_manager.inl
 */

#ifndef BINTJEKIT_ENTITY_ENTITY_MANAGER_INL
#define BINTJEKIT_ENTITY_ENTITY_MANAGER_INL
#pragma once

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
        auto type_index = std::type_index(typeid(EntityType));
        if (!m_collections.contains(type_index)) {
            create_collection<EntityType>();
        }
        return * static_cast<TypedCollection<EntityType>*>(
            m_collections.at(type_index).get());
    }

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    const TypedCollection<EntityType>& EntityManager::get_collection() const {
        auto type_index = std::type_index(typeid(EntityType));
        if (!m_collections.contains(type_index)) {
            m_logger->error("Collection {} does not exist", typeid(EntityType).name());
            throw std::runtime_error("Collection does not exist");
        }
        return * static_cast<const TypedCollection<EntityType>*>(
            m_collections.at(type_index).get());
    }

    template<typename... EntityTypes>
        requires (std::is_base_of_v<IEntity, EntityTypes> && ...)
    auto EntityManager::get() {
        return std::forward_as_tuple(std::ref(get_collection<EntityTypes>())...);
    }

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    void EntityManager::add(const std::shared_ptr<EntityType>& entity) {
        auto& collection = get_collection<EntityType>();
        m_entity_types.emplace(entity->id(), std::type_index(typeid(EntityType)));
        collection.add(entity);
    }

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    std::shared_ptr<EntityType> EntityManager::create() {
        auto& collection = get_collection<EntityType>();
        auto entity = collection.create();
        m_entity_types.emplace(entity->id(), std::type_index(typeid(EntityType)));
        return entity;
    }

    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    auto EntityManager::get(EntityId id) {
        if (m_entity_types.contains(id)) {
            auto entity_type = m_entity_types.find(id)->second;
            if (m_collections.contains(entity_type)) {
                auto& collection = * static_cast<TypedCollection<EntityType>*>(
                    m_collections.at(entity_type).get());
                return collection.get(id);
            }
            m_logger->warn("Collection {} does not exist", entity_type.name());
        }
        m_logger->warn("Entity {} does not exist", id);
        return std::shared_ptr<EntityType>();
    }
}

#endif // BINTJEKIT_ENTITY_ENTITY_MANAGER_INL
