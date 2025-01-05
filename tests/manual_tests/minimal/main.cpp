/*!
 * @file main.cpp
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
#include <memory>
#include "tools/logger/logger_define.hpp"
import core;
import factory;
import factory_child;
import logger;
int main() {
    bik::utils::logger::Logger::init();
    auto &logger = bik::utils::logger::Logger::getLogger();
    logger->info("TEst");
    LOGGER->info("Test define");
    LOGGER->flush();
    std::unique_ptr<bik::factory::Factory> factory = std::make_unique<bik::factory::Factory>();
    bik::core::Core core(std::move(factory));
    core.hw();
    bik::core::Core core_2(std::make_unique<min::Child>());
    core_2.hw();
    bik::core::Core core_3;
    core_3.hw();

    // core.configure();
    core.initialize();
    core.run();

    core_2.configure();
    // core_2.initialize();
    core_2.run();

    core_3.configure();
    core_3.initialize();
    core_3.run();

    return 0;
}
