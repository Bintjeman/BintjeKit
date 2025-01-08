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
#include "tools/logger/logger_define.hpp"
export module bik.playground:impl;
import :interface;
import bik.common;
namespace bik::playground {
    BasePlayGround::BasePlayGround() {
        LOGGER->info("BasePlayGround::BasePlayGround()");
    }

    BasePlayGround::~BasePlayGround() {
        LOGGER->info("BasePlayGround::~BasePlayGround()");
    }

    void BasePlayGround::configure() {
        LOGGER->info("BasePlayGround::configure()");
    }

    void BasePlayGround::initialize() {
        LOGGER->info("BasePlayGround::initialize()");
    }

    void BasePlayGround::update() {
        LOGGER->info("BasePlayGround::update()");
    }

    void BasePlayGround::finalize() {
        LOGGER->info("BasePlayGround::finalize()");
    }
}
