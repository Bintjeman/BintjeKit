/*!
 * @author bintjeman
 * @date 06.07.25
 * @name entitymanager.inl
 */
// entitymanager.inl
#ifndef BINTJEKIT_ENTITY_ENTITYMANAGER_INL
#define BINTJEKIT_ENTITY_ENTITYMANAGER_INL
#pragma once
namespace bnjkit {
    namespace entity {
        template<typename T>
        void EntityManager::register_entity_type() {
            auto typeIndex = std::type_index(typeid(T));
            if (!m_collections.contains(typeIndex)) {
                m_collections[typeIndex] = std::make_unique<HomogeneousGroup<T> >();
            }
        }
        template<typename EntityType>
        void EntityManager::add_entity(std::shared_ptr<EntityType> entity) {
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
        template<typename T>
        std::shared_ptr<T> EntityManager::get(EntityId id) {
            auto baseEntity = get_entity(id);
            auto result = std::dynamic_pointer_cast<T>(baseEntity);
            if (!result) {
                m_logger->error("Incorrect entity type");
                throw std::runtime_error("Incorrect entity type");
            }
            return result;
        }
        template<typename... Types>
        std::tuple<std::reference_wrapper<TypedEntityCollection<Types> >...>
        EntityManager::get_typed_collections() {
            return std::make_tuple(
                std::ref(m_collections[std::type_index(typeid(Types))]
                    ->template get_typed_collection<Types>())...
            );
        }
    }
}
#endif
