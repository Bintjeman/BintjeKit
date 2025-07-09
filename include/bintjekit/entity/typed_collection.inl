/*!
 * @author bintjeman
 * @date 08.07.25
 * @name typed_collection.inl
 */

#ifndef BINTJEKIT_ENTITY_TYPED_COLLECTION_INL
#define BINTJEKIT_ENTITY_TYPED_COLLECTION_INL
#pragma once
namespace bnjkit::entity {
    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    void TypedCollection<EntityType>::add(const EntityPtr& entity) {
        if (!entity) { return; }
        auto id = entity->id();
        m_entities.push_back(entity);
        m_registry[id] = m_entities.size() - 1;
    }

    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    typename TypedCollection<EntityType>::EntityPtr TypedCollection<EntityType>::create() {
        auto entity = std::make_shared<EntityType>();
        add(entity);
        return entity;
    }

    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    void TypedCollection<EntityType>::remove(EntityId id) {
        auto it = m_registry.find(id);
        if (it == m_registry.end()) { return; }
        // Déplacer la dernière entité à la position de l'entité supprimée
        std::size_t index = it->second;
        std::size_t last_index = m_entities.size() - 1;
        if (index != last_index) {
            m_entities[index] = m_entities[last_index];
            m_registry[m_entities[index]->id()] = index;
        }
        m_entities.pop_back();
        m_registry.erase(it);
    }

    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    typename TypedCollection<EntityType>::EntityPtr TypedCollection<EntityType>::get(EntityId id) const {
        auto it = m_registry.find(id);
        if (it == m_registry.end()) { return nullptr; }
        return m_entities[it->second];
    }
    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    std::vector<typename TypedCollection<EntityType>::EntityPtr>& TypedCollection<EntityType>::entities() {
        return m_entities;
    }
    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    const std::vector<typename TypedCollection<EntityType>::EntityPtr>& TypedCollection<EntityType>::entities() const {
        return m_entities;
    }

    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    const std::unordered_map<EntityId, std::size_t>& TypedCollection<EntityType>::registry() const {
        return m_registry;
    }

    template<typename EntityType> requires std::is_base_of_v<IEntity, EntityType>
    std::size_t TypedCollection<EntityType>::size() const {
        return m_entities.size();
    }
}
#endif // BINTJEKIT_ENTITY_TYPED_COLLECTION_INL
