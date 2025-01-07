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
import settings;
import logger;
int main() {
    std::cout << "Hello, World!" << std::endl;
    bik::logger::init("con_flogger.log", spdlog::level::trace);
    bik::config::Settings settings;
    settings.load("conf_settings.json");
    return 0;
}
