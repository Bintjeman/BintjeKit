/*!
 * @author bintjeman
 * @date 11.06.25
 * @name main.cpp
 * @example user_classes
 * @brief Example demonstrating custom module implementation using Bintjekit framework
 * 
 * This example shows how to create a simple animation of a bouncing circle using
 * custom implementations of Bintjekit core modules:
 * - MainWindow: Handles the SFML window
 * - EventManager: Processes window events
 * - Engine: Implements circle physics and state
 * - Renderer: Manages drawing
 * - EngineRenderer: Translates Engine state to drawable objects
 *
 * The circle bounces within window bounds, changing color on collision.
 * Features:
 * - Random movement direction
 * - Color changes on wall collision
 * - Window resize support
 * - Smooth animation
 *
 * The example demonstrates:
 * - Module inheritance and implementation
 * - CoreBuilder usage for dependency injection
 * - Integration between Engine and Renderer
 * - SFML drawing and event handling
 */
#include <memory>
#include <bintjekit/core/core.hpp>
#include <bintjekit/core/core_builder.hpp>
// #include <bintjekit/configuration/configuration_manager.hpp>
#include "main_window.hpp"
#include "event_manager.hpp"
#include "engine.hpp"
#include "engine_renderer.hpp"
#include "renderer.hpp"

int main() {
    auto core = bnjkit::core::CoreBuilder()
            .set_window_module(std::make_unique<usr::MainWindow>())
            .set_event_manager_module(std::make_unique<usr::EventManager>())
            .set_engine_module(std::make_unique<usr::Engine>())
            .set_renderer_module(std::make_unique<usr::Renderer>())
            .set_engine_renderer(std::make_unique<usr::EngineRenderer>())
            .build();
    core->run();

    return 0;
}
