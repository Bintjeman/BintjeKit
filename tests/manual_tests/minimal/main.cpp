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
#include <iostream>
#include <memory>
#include "tools/logger/logger_define.hpp"
import core;
import factory;
import factory_child;
import logger;
import settings_manager;
int main() {
    bik::config::Settings settings;
    try {
        settings.load("settings.json");
    } catch (...) {
        std::cerr << "Aucun fichier de configuration trouvé.\n";
    }
    bool jeux1 = settings.get_or_set("/Core 1", false);
    bool jeux2 = settings.get_or_set("/Core 2", true);
    bool jeux3 = settings.get_or_set("/Core 3", false);

    auto childSetting = settings.create_child("/Child");

    childSetting.set("test", 1);

    bik::utils::logger::Logger::init();
    auto &logger = bik::utils::logger::Logger::getLogger();
    logger->info("TEst");
    LOGGER->info("Test define");
    LOGGER->flush();
    if (jeux1) {
        std::unique_ptr<bik::factory::Factory> factory = std::make_unique<bik::factory::Factory>();
        bik::core::Core core(std::move(factory));
        core.hw();
        // core.configure();
        core.initialize();
        core.run();
    }
    if (jeux2) {
        bik::core::Core core_2(std::make_unique<min::Child>());
        core_2.hw();
        core_2.configure();
        // core_2.initialize();
        core_2.run();
    }
    if (jeux3) {
        bik::core::Core core_3;
        core_3.hw();
        core_3.configure();
        core_3.initialize();
        core_3.run();
    }
    settings.save("settings.json");
    return 0;
}
