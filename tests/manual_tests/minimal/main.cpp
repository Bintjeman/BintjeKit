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
import core;
import factory;
import logger;
int main() {
    bik::logger::init("logger.log", spdlog::level::debug);
    auto& logger = bik::logger::getLogger();
    bik::core::Core core;
    core.configure();
    core.initialize();
    core.run();
    core.finalize();
    return 0;
}
