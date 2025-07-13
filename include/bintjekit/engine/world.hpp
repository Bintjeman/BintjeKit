/*!
 * @author bintjeman
 * @date 13.07.25
 * @name world.hpp
 */

#ifndef BINTJEKIT_ENGINE_WORLD_HPP
#define BINTJEKIT_ENGINE_WORLD_HPP
#pragma once
#include "bintjekit/engine/entity_manager.hpp"
#include "bintjekit/engine/event/events.hpp"
#include "bintjekit/engine/event/event_manager.hpp"
#include "bintjekit/engine/prefab/prefab.hpp"

namespace bnjkit::engine {
    class ISystem;
    class World : public EntityManager {
    public:
        explicit World(const std::string& name);
        virtual ~World();
        // Méthodes spécifiques au gameplay
        template<typename... Components>
        entt::entity spawn(Components&&... components);

        void update();

        template<typename T>
        void add_system();

        // Gestion des prefabs
        void register_prefab(const std::string& name, PrefabData data);

        entt::entity spawn_prefab(const std::string& name);

    private:
        std::string m_name;
        std::vector<std::unique_ptr<ISystem> > m_systems;
        std::unique_ptr<EventBus> m_eventBus;
        std::unordered_map<std::string, PrefabData> m_prefabs;
    };
    // /////////////////////////////////////////////////////////////////////////
    template<typename... Components>
    entt::entity World::spawn(Components&&... components) {
        auto entity = create(std::forward<Components>(components)...);
        m_eventBus->emit(EntitySpawnedEvent{entity});
        return entity;
    }
    template<typename T>
    void World::add_system() {
        auto system = std::make_unique<T>();
        system->initialize(* this);
        m_systems.emplace_back(std::move(system));
    }
}
#endif // BINTJEKIT_ENGINE_WORLD_HPP
