/*!
 * @author bintjeman
 * @date 13.07.25
 * @name world.hpp
 */

#ifndef BINTJEKIT_ENGINE_ENGINE_HPP
#define BINTJEKIT_ENGINE_ENGINE_HPP
#pragma once
#include "gameplay_system_manager.hpp"
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/ecs/entity_manager.hpp"
#include "bintjekit/ecs/event/events.hpp"
#include "bintjekit/ecs/event/event_manager.hpp"
#include "bintjekit/engine/physic_system_manager.hpp"
#include "bintjekit/engine/gameplay_system_manager.hpp"

namespace bnjkit::ecs {
    class PrefabData;
    class ISystem;
}

namespace bnjkit::engine {
    struct PlayGround;

    class IEngine : public core::IModule, public ecs::EntityManager {
    public:
        enum class State {
            READY,
            RUNNING,
            PAUSED,
            CLOSED
        };
        IEngine();
        ~IEngine() override;

        void register_prefab(const std::string& name, ecs::PrefabData data);

        entt::entity spawn_prefab(const std::string& name);
        template<typename... Components>
        entt::entity spawn(Components&&... components);

        virtual void update();
        State state() const;
        [[nodiscard]] PlayGround& play_ground();
        [[nodiscard]] const PlayGround& play_ground() const;


    protected:
        void set_state(State state);
        State m_state{State::CLOSED};
        PhysicsSystemManager m_physics_system_manager;
        GameplaySystemManager m_gameplay_system_manager;
        std::unique_ptr<PlayGround> m_play_ground;

    private:
        std::unordered_map<std::string, ecs::PrefabData> m_prefabs;
        std::unique_ptr<ecs::EventBus> m_eventBus;
    };
    // /////////////////////////////////////////////////////////////////////////
    template<typename... Components>
    entt::entity IEngine::spawn(Components&&... components) {
        auto entity = create(std::forward<Components>(components)...);
        m_eventBus->emit(ecs::EntitySpawnedEvent{entity});
        return entity;
    }
}
#endif // BINTJEKIT_ENGINE_ENGINE_HPP
