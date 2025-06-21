/*!
 * @author bintjeman
 * @date 19.06.25
 * @name main.cpp
 */
#include <spdlog/spdlog.h>
#include <memory>
#include <bintjekit/core.hpp>
#include <bintjekit/configuration.hpp>
#include <bintjekit/logger.hpp>
#include "engine/TotoEngine.hpp"
#include "default_json.inl"

// int main() {
//     bnjkit::core::Logger::initialize();  // Vérifiez si cette étape est présente
//     auto logger = bnjkit::core::Logger::get_logger(bnjkit::core::module_names::APP);
//     // logger->info("Starting toto app");
//     auto core = bnjkit::core::CoreBuilder()
//             .set<toto::TotoEngine>()
//             .build();
//     auto settings = core->settings();
//     settings.set_default_values(default_json);
//     settings.load_from_json(bnjkit::conf::from_file("conf.json"));
//     // auto logger = bnjkit::core::Logger::get_logger(bnjkit::core::module_names::APP);
//     // logger->info("Settings loaded");
//     std::string title = settings.get<std::string>("/title"_json_pointer);
//     // logger->trace(title);
//     core->run();
//     settings.save_to_file("conf.json");
//     return 0;
// }
#include <iostream>
int main() {
    try {
        std::cout << "SPDLOG VERSION: " << SPDLOG_VER_MAJOR << "." << SPDLOG_VER_MINOR << "." << SPDLOG_VER_PATCH << std::endl;

        bnjkit::core::Logger::initialize();
        std::shared_ptr<spdlog::logger> logger = bnjkit::core::Logger::get_logger(bnjkit::core::module_names::APP);
        std::cout << "Logger créé" << std::endl;
        logger->info("Hello world!");
        // ... reste du code
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

}