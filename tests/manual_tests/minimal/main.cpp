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

import core;
import factory;
import logger;
int main() {
    bik::logger::init("logger.log", spdlog::level::trace);
    auto& logger = bik::logger::getLogger();
    logger->info("Hello world !");
    bik::core::Core core;
    logger->flush();
    core.configure();
    logger->flush();
    core.initialize();
    logger->flush();
    core.run();
    logger->flush();
    core.finalize();
    logger->flush();
    return 0;
}
