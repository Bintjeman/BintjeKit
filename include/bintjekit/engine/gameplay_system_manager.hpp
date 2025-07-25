/*!
 * @author bintjeman
 * @date 16.07.25
 * @name gameplay_system_manager.hpp
 */

#ifndef BINTJEKIT_ENGINE_GAMEPLAY_SYSTEM_MANAGER_HPP
#define BINTJEKIT_ENGINE_GAMEPLAY_SYSTEM_MANAGER_HPP
#pragma once
#include "bintjekit/ecs/system/i_system.hpp"
#include "bintjekit/ecs/i_system_manager.hpp"
namespace bnjkit::engine {
    enum class GameplayPriority {
        INPUT = 0,
        LOGIC = 100,
        AI = 200,
        POST_UPDATE = 300
    };
    class GameplaySystemManager final : public ecs::SystemManager<ecs::ISystem, GameplayPriority> {
    public:
        ~GameplaySystemManager() override;
    };
}

#endif //BINTJEKIT_ENGINE_GAMEPLAY_SYSTEM_MANAGER_HPP
