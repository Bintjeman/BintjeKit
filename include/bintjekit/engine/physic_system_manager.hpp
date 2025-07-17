/*!
 * @author bintjeman
 * @date 16.07.25
 * @name physic_system_manager.hpp
 */

#ifndef BINTJEKIT_ENGINE_PHYSIC_SYSTEM_MANAGER_HPP
#define BINTJEKIT_ENGINE_PHYSIC_SYSTEM_MANAGER_HPP
#pragma once
#include "bintjekit/ecs/system/i_system.hpp"
#include "bintjekit/ecs/i_system_manager.hpp"
namespace bnjkit::engine {
    enum class PhysicsPriority {
        PRE_STEP = 0,
        COLLISION = 100,
        POST_STEP = 200
    };
    class PhysicsSystemManager : public ecs::SystemManager<ecs::ISystem, PhysicsPriority> {
    public:
        void step_simulation();
    };
}
#endif //BINTJEKIT_ENGINE_PHYSIC_SYSTEM_MANAGER_HPP
