/*!
 * @author bintjeman
 * @date 13.07.25
 * @name world.hpp
 */

#ifndef BINTJEKIT_ENGINE_WORLD_HPP
#define BINTJEKIT_ENGINE_WORLD_HPP
#pragma once
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/ecs/entity_manager.hpp"
#include "bintjekit/ecs/event/events.hpp"
#include "bintjekit/ecs/event/event_manager.hpp"

namespace bnjkit::engine {
    struct PlayGround;
    struct PrefabData;
    class ISystem;

    class IWorld : public core::IModule, public ecs::EntityManager {
    public:
        explicit IWorld(const std::string& name);
        ~IWorld() override;

        void register_prefab(const std::string& name, PrefabData data);
        virtual void add_system(std::unique_ptr<ISystem> system) = 0;
        virtual void remove_system(const std::string& name) = 0;

        entt::entity spawn_prefab(const std::string& name);
        template<typename... Components>
        entt::entity spawn(Components&&... components);

        void update();

        [[nodiscard]] std::string name() const override;
        [[nodiscard]] PlayGround& play_ground();
        [[nodiscard]] const PlayGround& play_ground() const;
    protected:
        std::string m_name;
        std::unique_ptr<PlayGround> m_play_ground;
    private:
        std::vector<std::unique_ptr<ISystem> > m_systems;
        std::unique_ptr<ecs::EventBus> m_eventBus;
        std::unordered_map<std::string, PrefabData> m_prefabs;
    };
    // /////////////////////////////////////////////////////////////////////////
    template<typename... Components>
    entt::entity IWorld::spawn(Components&&... components) {
        auto entity = create(std::forward<Components>(components)...);
        m_eventBus->emit(ecs::EntitySpawnedEvent{entity});
        return entity;
    }
}
#endif // BINTJEKIT_ENGINE_WORLD_HPP
