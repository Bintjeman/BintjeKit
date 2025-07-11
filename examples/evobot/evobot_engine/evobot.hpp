/*!
 * @author bintjeman
 * @date 27.06.25
 * @name evobot.hpp
 */

#ifndef EVOBOT_HPP
#define EVOBOT_HPP
#pragma once
#include "evobot_engine/bot.hpp"

namespace evo::engine {
    class Evobot : public Bot {
    public:
        Evobot();
        ~Evobot() override;
        void update() override;
    };
}

#endif //EVOBOT_HPP
