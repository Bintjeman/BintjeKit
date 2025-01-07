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
import factory;
import bik.core;
import bik.logger;
int main() {
    std::cout << "Hello, World!" << std::endl;
    bik::logger::init("logger.log", spdlog::level::trace);
    bik::core::Core core(std::make_unique<Factory>());
    core.configure();
    core.initialize();
    core.run();
    core.finalize();
    return 0;
}
