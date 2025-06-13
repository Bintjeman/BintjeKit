/*!
 * @author bintjeman
 * @date 11.06.25
 * @name main.cpp
 */
#include <memory>
#include <bintjekit/core/core.hpp>
#include "bintjekit/core/core_builder.hpp"
#include "main_window.hpp"
#include "event_manager.hpp"
#include "engine.hpp"
#include "renderer.hpp"
int main() {
    auto core = bnjkit::core::CoreBuilder()
            .set_window_module(std::make_unique<usr::MainWindow>())
            .set_event_manager_module(std::make_unique<usr::EventManager>())
            .set_engine_module(std::make_unique<usr::Engine>())
            .set_renderer_module(std::make_unique<usr::Renderer>())
            .build();
    core->run();
    return 0;
}
