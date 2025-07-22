/*!
 * @author bintjeman
 * @date 13.07.25
 * @name events.hpp
 *
 */
 /*!
  * @todo Mettre en place le system event dans le module ECS
  */
#ifndef BINTJEKIT_ECS_EVENTS_HPP
#define BINTJEKIT_ECS_EVENTS_HPP
#pragma once
#include <entt/entity/entity.hpp>
namespace bnjkit::ecs {
    /*!
     * @todo implémenter cette class
     *
     * Pour l'instant cette class n'est pas du tout utilisée.
     */
    struct EntitySpawnedEvent {
        entt::entity entity;
    };

    struct EntityDestroyedEvent {
        entt::entity entity;
    };

    // On peut ajouter d'autres événements ici
    struct CollisionEvent {
        entt::entity entity1;
        entt::entity entity2;
    };
} // namespace bnjkit::engine

#endif // BINTJEKIT_ECS_EVENTS_HPP
