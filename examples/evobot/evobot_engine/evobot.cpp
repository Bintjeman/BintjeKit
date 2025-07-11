/*!
 * @author bintjeman
 * @date 27.06.25
 * @name evobot.cpp
 */
#include "evobot.hpp"

namespace evo::engine {
    Evobot::Evobot() = default;
    Evobot::~Evobot() = default;
    void Evobot::update() {
        Bot::update();
    }
}
