/*!
 * @author bintjeman
 * @date 06.07.25
 * @name entitymanager.inl
 */
// entitymanager.inl
#ifndef BINTJEKIT_ENTITY_ENTITYMANAGER_INL
#define BINTJEKIT_ENTITY_ENTITYMANAGER_INL
#pragma once
namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    EntityManager<BaseEntity>::EntityManager() {
        m_logger = spdlog::get("entity_manager");
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    EntityManager<BaseEntity>::~EntityManager() = default;

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    void EntityManager<BaseEntity>::update() {
        for (const auto& collection: m_collections | std::views::values) {
            for (auto& entity: collection->get_collection()) {
                if (entity) {
                    entity->update();
                }
            }
        }
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
        requires std::derived_from<T, BaseEntity>
    void EntityManager<BaseEntity>::register_entity_type() {
        if (const auto type_index = std::type_index(typeid(T)); !m_collections.contains(type_index)) {
            m_collections[type_index] = std::make_unique<HomogeneousGroup<T> >();
        }
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
        requires std::derived_from<T, BaseEntity>
    void EntityManager<BaseEntity>::add_entity(std::shared_ptr<T> entity) {
        if (!entity || !entity->valid()) {
            m_logger->error("Entity is invalid");
            throw std::invalid_argument("Entity is invalid");
        }
        auto type_index = std::type_index(typeid(T));
        if (!m_collections.contains(type_index)) {
            m_collections[type_index] = std::make_unique<HomogeneousGroup<T> >();
        }
        m_collections[type_index]->add_entity(entity);
        m_global_registry.emplace(
            entity->id(),
            std::pair<std::type_index, std::weak_ptr<BaseEntity> >{
                type_index,
                std::weak_ptr<BaseEntity>(entity)
            }
        );
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
        requires std::derived_from<T, BaseEntity>
    std::shared_ptr<T> EntityManager<BaseEntity>::create_entity() {
        auto entity = std::make_shared<T>();
        add_entity(entity);
        return entity;
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    template<typename T>
        requires std::derived_from<T, BaseEntity>
    std::shared_ptr<T> EntityManager<BaseEntity>::get(const EntityId id) {
        auto base_entity = get_entity(id);
        auto result = std::dynamic_pointer_cast<T>(base_entity);
        if (!result) {
            m_logger->error("Incorrect entity type");
            throw std::runtime_error("Incorrect entity type");
        }
        return result;
    }
    template<typename BaseEntity> requires std::derived_from<BaseEntity, IEntity>
    std::vector<std::shared_ptr<BaseEntity> > EntityManager<BaseEntity>::get_entities() const {
        std::vector<std::shared_ptr<BaseEntity> > all_entities;
        all_entities.reserve(m_global_registry.size()); // Pré-allouer pour les performances
        for (const auto& collection: m_collections | std::views::values) {
            const auto& entities = collection->get_collection();
            all_entities.insert(
                all_entities.end(),
                entities.begin(),
                entities.end()
            );
        }

        return all_entities;
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    std::shared_ptr<BaseEntity> EntityManager<BaseEntity>::get_entity(EntityId id) {
        auto it = m_global_registry.find(id);
        if (it == m_global_registry.end()) {
            m_logger->error("Entity not found: {}", id);
            throw std::runtime_error("Entity not found");
        }
        if (auto entity = it->second.second.lock()) {
            return entity;
        }
        m_logger->error("Entity expired: {}", id);
        throw std::runtime_error("Entity expired");
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    void EntityManager<BaseEntity>::remove_entity(EntityId id) {
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

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    void EntityManager<BaseEntity>::clear() {
        m_collections.clear();
        m_global_registry.clear();
        m_custom_groups.clear();
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    typename EntityManager<BaseEntity>::CustomGroupType&
    EntityManager<BaseEntity>::create_group(const typename CustomGroupType::GroupId& group_id) {
        return m_custom_groups.emplace(group_id, CustomGroupType(* this, group_id)).first->second;
    }

    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    typename EntityManager<BaseEntity>::CustomGroupType*
    EntityManager<BaseEntity>::get_group(const typename CustomGroupType::GroupId& group_id) {
        auto it = m_custom_groups.find(group_id);
        return it != m_custom_groups.end() ? & it->second : nullptr;
    }
}
#endif
