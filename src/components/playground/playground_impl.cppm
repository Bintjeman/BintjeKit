/*!
 * @file simulation_impl.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "tools/logger/logger_define.hpp"
export module bik.playground:impl;
import :interface;
import bik.common;
import bik.settings;
namespace bik::playground {
    BasePlayGround::BasePlayGround() {
        LOGGER->info("BasePlayGround::BasePlayGround()");
    }

    BasePlayGround::~BasePlayGround() {
        LOGGER->info("BasePlayGround::~BasePlayGround()");
    }

    void BasePlayGround::update() {
        LOGGER->info("BasePlayGround::update()");
    }

    void BasePlayGround::finalize() {
        LOGGER->info("BasePlayGround::finalize()");
    }

    sf::Rect<float> BasePlayGround::boundaries() const {
        return sf::Rect<float>();
    }
}
