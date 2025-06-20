/*!
 * @author bintjeman
 * @date 14.06.25
 * @name main.cpp
 */
#include <bintjekit/core.hpp>
// #include <bintjekit/core/core.hpp>
// #include <bintjekit/core/core_builder.hpp>
#include "game_of_life.hpp"
#include "game_of_life_renderer.hpp"
#include "renderer.hpp"
#include "core_event_handler.hpp"
#include "bintjekit/configuration.hpp"
#include "default_json.inl"
#include "bintjekit/configuration/utils.hpp"
int main() {
    auto core = bnjkit::core::CoreBuilder()
            .set<gol::GameOfLife>()
            .set<gol::GameOfLifeRenderer>()
            .set<gol::Renderer>()
            .set<gol::CoreEventHandler>()
            .build();
    auto settings = core->settings();
    settings.set_default_values(default_json);
    settings.load_from_json(bnjkit::conf::from_file("conf.json"));
    settings.set_path("conf.json");
    core->run();
    settings.save_to_file();
    return 0;
}
