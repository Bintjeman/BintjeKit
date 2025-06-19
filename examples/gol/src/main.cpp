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

int main() {
    auto core = bnjkit::core::CoreBuilder()
            .set<gol::GameOfLife>()
            .set<gol::GameOfLifeRenderer>()
            .set<gol::Renderer>()
            .set<gol::CoreEventHandler>()
            .build();
    core->run();
    return 0;
}
