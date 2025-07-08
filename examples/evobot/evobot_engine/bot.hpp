/*!
 * @author bintjeman
 * @date 04.07.25
 * @name bot.hpp
 */

#ifndef BOT_HPP
#define BOT_HPP
#pragma once
#include "entity.hpp"
namespace evo::engine {
    class Bot : public Entity {
    public:
        Bot();
        ~Bot() override;

    private:
    };
}

#endif //BOT_HPP
