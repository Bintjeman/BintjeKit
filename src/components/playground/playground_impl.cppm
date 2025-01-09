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
import bik.settings;
namespace bik::playground {
    BasePlayGround::BasePlayGround() {
        LOGGER->info("BasePlayGround::BasePlayGround()");
    }

    BasePlayGround::~BasePlayGround() {
        LOGGER->info("BasePlayGround::~BasePlayGround()");
    }

    void BasePlayGround::configure(config::Child settings) {
        LOGGER->info("BasePlayGround::configure()");
        settings_ = settings;
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