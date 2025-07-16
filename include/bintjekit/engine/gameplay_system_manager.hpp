/*!
 * @author bintjeman
 * @date 16.07.25
 * @name gameplay_system_manager.hpp
 */

#ifndef GAMEPLAY_SYSTEM_MANAGER_HPP
#define GAMEPLAY_SYSTEM_MANAGER_HPP
#pragma once
#include "bintjekit/ecs/i_system_manager.hpp"
#include "bintjekit/ecs/system/i_system.hpp"
namespace bnjkit::engine {
    enum class GameplayPriority {
        INPUT = 0,
        LOGIC = 100,
        AI = 200,
        POST_UPDATE = 300
    };
    class GameplaySystemManager : public ecs::SystemManager<ISystem, GameplayPriority> {
    public:
        void process_game_logic(float deltaTime);
    };
}

#endif //GAMEPLAY_SYSTEM_MANAGER_HPP
