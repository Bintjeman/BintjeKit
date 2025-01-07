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
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "tools/logger/logger_define.hpp"
import settings;
import logger;
int main() {
    std::cout << "Hello, World!" << std::endl;
    bik::logger::init("con_flogger.log", spdlog::level::trace);
    // bik::config::Settings settings;
    // settings.load("conf_settings.json", bik::config::Settings::LoadMode::NOTHING);

    bik::config::Settings settings2;
    settings2.load("conf_settings.json", bik::config::Settings::LoadMode::CREATE);

    settings2.set("/valeur1"_json_pointer, 100);
    int valeur1 = settings2.get("/valeur1"_json_pointer, 6);
    LOGGER->info("valeur1: {}", valeur1);

    settings2.set("/Valeur/imbriquée"_json_pointer, 200);
    int valeurimbriquee = settings2.get("/Valeur/imbriquée"_json_pointer, 6);
    LOGGER->info("valeurimbriquee: {}", valeurimbriquee);


    auto settings2_child = settings2.create_child("/enfantdirect"_json_pointer);
    settings2_child.set("/valeur1dansenfant"_json_pointer, 300);
    int valeurenfantdirect = settings2_child.get("/valeur1dansenfant"_json_pointer, 6);
    LOGGER->info("valeurenfantdirect: {}", valeurenfantdirect);

    settings2.set("/enfantdirect/valeur1dansenfant"_json_pointer, 400);
    valeurenfantdirect = settings2_child.get("/valeur1dansenfant"_json_pointer, 6);
    LOGGER->info("valeurenfantdirect: {}", valeurenfantdirect);
    settings2.get_or_set("/enfantdirect/valeur1dansenfant666"_json_pointer, 666);

    settings2.save("conf_settings.json");

    return 0;
}
