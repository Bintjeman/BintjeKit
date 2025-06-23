/*!
 * @author bintjeman
 * @date 14.06.25
 * @name main.cpp
 */
#include "bintjekit/core.hpp"
#include "bintjekit/configuration.hpp"
#include "bintjekit/logger.hpp"
#include "game_of_life.hpp"
#include "game_of_life_renderer.hpp"
#include "renderer.hpp"
#include "core_event_handler.hpp"
// #include "bintjekit/configuration.hpp"
#include "default_json.inl"
int main() {
    auto logger = bnjkit::core::Logger::get_logger(bnjkit::core::module_names::APP);
    logger->set_level(spdlog::level::trace);
    bnjkit::core::Logger::get_logger(bnjkit::core::module_names::CONFIGURATION)->set_level(
        spdlog::level::trace);
    bnjkit::core::Logger::get_logger(bnjkit::core::module_names::WINDOW)->set_level(
        spdlog::level::trace);
    logger->info("Starting toto app");
    auto core = bnjkit::core::CoreBuilder()
            .set<gol::GameOfLife>()
            .set<gol::GameOfLifeRenderer>()
            .set<gol::Renderer>()
            .set<gol::CoreEventHandler>()
            .build();

    auto& settings = core->settings();
    settings.set_default_values(default_json);
    settings.load_from_json(bnjkit::conf::from_file("conf.json"), true);
    settings.set_path("conf.json");
    core->configure();
    logger->trace("Settings before run:  {}", settings.to_string());
    core->run();
    logger->trace("Settings after run:  {}", settings.to_string());
    settings.save_to_file();
    return 0;
}
