/*!
 * @file main.cpp
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
#include <memory>
#include "tools/logger/logger_define.hpp"
import gol.factory;
import bik.core;
import bik.logger;
int main() {
    bik::logger::init("gol_logger.log", spdlog::level::trace);
    LOGGER->flush_on(spdlog::level::info);
    bik::core::Core core(std::make_unique<gol::Factory>());
    core.configure();
    core.initialize();
    core.run();
    LOGGER->flush();
    return 0;
}
