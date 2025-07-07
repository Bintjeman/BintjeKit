/*!
 * @author bintjeman
 * @date 07.07.25
 * @name EntityManager.hpp
 */
#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
#pragma once
#include <type_traits>
#include <unordered_map>
#include <typeindex>
#include <tuple>
#include "bintjekit/entity/ientity.hpp"
#include "entity_collection.hpp"

namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    class EntityManager {
    public:
        EntityManager();
        ~EntityManager() = default;

        // Méthodes pour enregistrer un nouveau type d'entité
        template<typename T>
            requires std::is_base_of_v<BaseEntity, T>        void register_type();

        // Méthodes pour ajouter/créer des entités
        template<typename T>
            requires std::is_base_of_v<BaseEntity, T>        void add(const std::shared_ptr<T>& entity);

        template<typename T>
            requires std::is_base_of_v<BaseEntity, T>        std::shared_ptr<T> create(EntityId id);

        // Obtenir une collection typée spécifique
        template<typename T>
            requires std::is_base_of_v<BaseEntity, T>        EntityCollectionManager<T>& get_collection();

        // Obtenir plusieurs collections typées
        template<typename... Types>
            requires (std::is_base_of_v<Types, BaseEntity> && ...)
        auto get_typed_collections() {
            return std::make_tuple(std::ref(get_collection<Types>())...);
        }
        template<typename... Types>
            requires (std::is_base_of_v<Types, BaseEntity> && ...)
        auto get_typed_collections() const {
            return std::make_tuple(std::ref(get_collection<Types>())...);
        }

        // Obtenir toutes les entités
        [[nodiscard]] EntityCollection get_all_entities() const;

        void remove(EntityId id);
        void clear();

    private:
        std::unordered_map<
            std::type_index,
            std::unique_ptr<EntityCollectionManager<BaseEntity> >
        > m_collections;

        std::shared_ptr<spdlog::logger> m_logger;
    };
}

#include "entity_manager.inl"
#endif //ENTITYMANAGER_HPP
