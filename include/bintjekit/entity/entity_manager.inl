/*!
 * @author bintjeman
 * @date 07.07.25
 * @name entity_manager.inl
 */
// entity_manager.inl
#ifndef ENTITY_MANAGER_INL
#define ENTITY_MANAGER_INL
#pragma once
#define DEBUG_TEST_NOT_FOUND_RETURN_DEFAULT
#ifndef DEBUG_TEST_NOT_FOUND_RETURN_DEFAULT
#define DEBUG_TEST_NOT_FOUND_RETURN_ERROR
#endif
static constexpr size_t INITIAL_COLLECTION_CAPACITY = 16;

namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    EntityManager<BaseEntity>::EntityManager() {
        m_logger = core::Logger::get_logger(core::module_names::ENTITY);
        EntityCollectionManager<BaseEntity>::set_logger(m_logger);
        m_collections.reserve(INITIAL_COLLECTION_CAPACITY);
        m_logger->info("Entity manager created");
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    template<typename T>
        requires std::is_base_of_v<BaseEntity, T>
    void EntityManager<BaseEntity>::register_type() {
        m_logger->trace("Registering type {}", typeid(T).name());
        auto type_index = std::type_index(typeid(T));
        if (m_collections.size() == m_collections.max_size()) {
            m_logger->error("Unable to add more collections - maximum limit reached");
            throw std::runtime_error("Collection limit reached");
        }
        if (!m_collections.contains(type_index)) {
            if (m_collections.size() + 1 > m_collections.bucket_count()) {
                m_collections.reserve(m_collections.size() * 2);
            }
            m_collections[type_index] = std::make_unique<EntityCollectionManager<T> >();
        }
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    template<typename T>
        requires std::is_base_of_v<BaseEntity, T>
    void EntityManager<BaseEntity>::add(const std::shared_ptr<T>& entity) {
        m_logger->trace("Adding entity {}: {}", entity->id(), typeid(T).name());
        auto type_index = std::type_index(typeid(T));
        if (!m_collections.contains(type_index)) {
            register_type<T>();
        }
        auto& collection = get_collection<T>();
        collection.add(entity);
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    template<typename T>
        requires std::is_base_of_v<BaseEntity, T>
    std::shared_ptr<T> EntityManager<BaseEntity>::create() {
        m_logger->trace("Creating entity: type: {}", typeid(T).name());
        auto& collection = get_collection<T>();
        return std::dynamic_pointer_cast<T>(collection.create());
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    template<typename T>
        requires std::is_base_of_v<BaseEntity, T>
    EntityCollectionManager<T>& EntityManager<BaseEntity>::get_collection() {
        auto type_index = std::type_index(typeid(T));
        if (!m_collections.contains(type_index)) {
            register_type<T>();
        }
        return * dynamic_cast<EntityCollectionManager<T>*>(m_collections[type_index].get());
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    template<typename T>
        requires std::is_base_of_v<BaseEntity, T>
    const EntityCollectionManager<T>& EntityManager<BaseEntity>::get_collection() const {
        auto type_index = std::type_index(typeid(T));
        if (!m_collections.contains(type_index)) {
            m_logger->error("Typed {} collection not found", type_index.name());
#ifdef DEBUG_TEST_NOT_FOUND_RETURN_ERROR
            throw std::runtime_error("Typed collection not found");
#endif
#ifdef DEBUG_TEST_NOT_FOUND_RETURN_DEFAULT
            static const EntityCollectionManager<T> empty_collection;
            return empty_collection;
#endif
        }
        return * dynamic_cast<EntityCollectionManager<T>*>(m_collections.at(type_index).get());
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    EntityCollection EntityManager<BaseEntity>::get_all_entities() const {
        EntityCollection all_entities;
        for (const auto& [_, collection]: m_collections) {
            auto entities = collection->get_entities();
            all_entities.insert(
                all_entities.end(),
                entities.begin(),
                entities.end()
            );
        }
        return all_entities;
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    void EntityManager<BaseEntity>::remove(EntityId id) {
        for (auto& [_, collection]: m_collections) {
            collection->remove(id);
        }
    }

    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    void EntityManager<BaseEntity>::clear() {
        for (auto& [_, collection]: m_collections) {
            collection->clear();
        }
    }
}
#endif
