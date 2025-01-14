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
#include <spdlog/spdlog.h>
import min.factory;
import bik.core;
import bik.logger;
import min.playground;
import min.ui;
int main() {
    bik::logger::init("logger.log", spdlog::level::trace);
    auto &logger = bik::logger::getLogger();
    bik::core::Core core(std::make_unique<min::Factory>());
    core.configure();
    core.initialize();
    core.run();
    logger->debug("core: closed");
    return 0;
}
