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
export module bik.simulation:impl;
import :interface;
import bik.common;
namespace bik::simulation {
    BaseSimulation::BaseSimulation() {
        LOGGER->info("BaseSimulation::BaseSimulation()");
    }

    BaseSimulation::~BaseSimulation() {
        LOGGER->info("BaseSimulation::~BaseSimulation()");
    }

    void BaseSimulation::configure() {
        LOGGER->info("BaseSimulation::configure()");
    }

    void BaseSimulation::initialize() {
        LOGGER->info("BaseSimulation::initialize()");
    }

    void BaseSimulation::update() {
        LOGGER->info("BaseSimulation::update()");
    }

    void BaseSimulation::finalize() {
        LOGGER->info("BaseSimulation::finalize()");
    }
}
