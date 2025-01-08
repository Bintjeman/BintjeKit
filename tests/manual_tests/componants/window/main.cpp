/*!
 * @file main.cpp
 * @author bintjeman
 * @date 07.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
#include <iostream>
#include "tools/logger/logger_define.hpp"
import factory;
import bik.core;
import bik.logger;
int main() {
    bik::logger::init("logger.log", spdlog::level::trace);
    bik::core::Core core(std::make_unique<tst::Factory>());
    LOGGER->flush();
    core.configure();
    core.initialize();
    core.run();
    core.finalize();
    return 0;
}
