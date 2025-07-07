/*!
* @author bintjeman
 * @date 26.06.25
 * @name entitymanager.hpp
 */
// entitymanager.hpp
#ifndef BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#define BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#pragma once

#include <memory>
#include <typeindex>
#include <spdlog/fwd.h>
#include "bintjekit/entity/entity_helper.hpp"
#include "bintjekit/entity/collection.hpp"
#include "bintjekit/entity/custom_group.hpp"

namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::derived_from<BaseEntity, IEntity>
    class EntityManager {
    public:
        using CustomGroupType = CustomGroup<BaseEntity>;

        EntityManager();
        ~EntityManager();
        void update();

        template<typename T> requires std::derived_from<T, BaseEntity>
        void register_entity_type();

        template<typename T> requires std::derived_from<T, BaseEntity>
        void add_entity(std::shared_ptr<T> entity);

        template<typename T> requires std::derived_from<T, BaseEntity>
        std::shared_ptr<T> create_entity();

        std::shared_ptr<BaseEntity> get_entity(EntityId id);

        template<typename T> requires std::derived_from<T, BaseEntity>
        std::shared_ptr<T> get(EntityId id);

        const std::unordered_map<std::type_index, std::unique_ptr<Collection> >&
        get_collections() const {
            return m_collections;
        }

        [[nodiscard]] std::vector<std::shared_ptr<BaseEntity> > get_entities() const ;

        template<typename... Types>
            requires (std::derived_from<Types, BaseEntity> && ...)
        auto get_typed_collections() {
            return std::make_tuple(TypedCollection<Types>(* this)...);
        }

        void remove_entity(EntityId id);
        void clear();

        CustomGroupType& create_group(const typename CustomGroupType::GroupId& group_id);
        CustomGroupType* get_group(const typename CustomGroupType::GroupId& group_id);

    private:
        template<typename T>
        class TypedCollection {
        public:
            explicit TypedCollection(EntityManager& manager) : m_manager(manager) {}

            auto& get() {
                const auto typeIndex = std::type_index(typeid(T));
                auto it = m_manager.m_collections.find(typeIndex);
                if (it == m_manager.m_collections.end()) {
                    m_manager.m_logger->error("Collection not found for type {}", typeid(T).name());
                    throw std::runtime_error("Collection not found");
                }
                return it->second->get_collection();
            }

        private:
            EntityManager& m_manager;
        };

        std::unordered_map<std::type_index, std::unique_ptr<Collection> > m_collections;
        std::unordered_map<EntityId, std::pair<std::type_index, std::weak_ptr<BaseEntity> > >
        m_global_registry;
        std::unordered_map<typename CustomGroupType::GroupId, CustomGroupType> m_custom_groups;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}

#include "entity_manager.inl"
#endif
