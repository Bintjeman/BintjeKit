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
import bik.core;
import bik.factory;
import bik.logger;
import bik.window;
int main() {
    bik::logger::init("logger.log", spdlog::level::trace);
    auto& logger = bik::logger::getLogger();
    bik::core::Core core;
    core.configure();
    core.initialize();
    core.run();
   return 0;
}

