/*!
 * @author bintjeman
 * @date 13.07.25
 * @name events.hpp
 */

#ifndef EVENTS_HPP
#define EVENTS_HPP
#pragma once

namespace bnjkit::engine {
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

#endif //EVENTS_HPP
