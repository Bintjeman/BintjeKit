/*!
 * @author bintjeman
 * @date 13.07.25
 * @name entity_manager.hpp
 */

#ifndef BINTJEKIT_ECS_ENTITY_MANAGER_HPP
#define BINTJEKIT_ECS_ENTITY_MANAGER_HPP
#pragma once
#include <entt/entt.hpp>
namespace bnjkit::ecs {
    class EntityManager {
    public:
        /*!
         * Class helper pour la gestion des entity avec entt.
         */
        EntityManager();
        virtual ~EntityManager();
        /*!
         * @return Le registre entt des entités
         */
        entt::registry& registry();
        [[nodiscard]] const entt::registry& registry() const;

        template<typename... Components>
        entt::entity create(Components&&... components);

        void destroy(entt::entity entity);

        template<typename T>
        T& get(entt::entity entity);

        template<typename T, typename... Args>
        T& add(entt::entity entity, Args&&... args);

        template<typename... Components>
        auto view();

        void clear();

    protected:
        // std::shared_ptr<spdlog::logger> m_logger;
        entt::registry m_registry;
    };
    // /////////////////////////////////////////////////////////////////////////
    template<typename... Components>
    entt::entity EntityManager::create(Components&&... components) {
        auto entity = m_registry.create();
        (m_registry.emplace<Components>(entity, std::forward<Components>(components)), ...);
        return entity;
    }
    template<typename T>
    T& EntityManager::get(entt::entity entity) {
        return m_registry.get<T>(entity);
    }
    template<typename T, typename... Args>
    T& EntityManager::add(entt::entity entity, Args&&... args) {
        return m_registry.emplace<T>(entity, std::forward<Args>(args)...);
    }
    template<typename... Components>
    auto EntityManager::view() {
        return m_registry.view<Components...>();
    }
}

#endif // BINTJEKIT_ECS_ENTITY_MANAGER_HPP
