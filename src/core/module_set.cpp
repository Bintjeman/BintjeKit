/*!
 * @author bintjeman
 * @date 16.07.25
 * @name module_set.cpp
 */
#include "bintjekit/core/module_set.hpp"
#include "bintjekit/logger.hpp""
#include "bintjekit/core/modules.hpp"

namespace bnjkit::core {
    ModuleSet::ModuleSet() {
        m_logger = Logger::get_logger(literals::logger::CORE);
        m_logger->info("Constructor of ModuleSet");
    }
    ModuleSet::~ModuleSet() {
        m_logger->info("Destructor of ModuleSet");
    }
    window::IMainWindow& ModuleSet::get_window() {
        return * m_window;
    }
    renderer::IRenderer& ModuleSet::get_renderer() {
        return * m_renderer;
    }
    event::ICoreEventHandler& ModuleSet::get_core_event_handler() {
        return * m_core_event_handler;
    }
    engine::IEngine& ModuleSet::get_world() {
        return * m_world;
    }
    window::IMainWindow& ModuleSet::get_window() const {
        return * m_window;
    }
    renderer::IRenderer& ModuleSet::get_renderer() const {
        return * m_renderer;
    }
    event::ICoreEventHandler& ModuleSet::get_core_event_handler() const {
        return * m_core_event_handler;
    }
    engine::IEngine& ModuleSet::get_world() const {
        return * m_world;
    }
    void ModuleSet::set_window(std::unique_ptr<window::IMainWindow> window) {
        m_logger->trace("Setting window");
        m_window = std::move(window);
    }
    void ModuleSet::set_renderer(std::unique_ptr<renderer::IRenderer> renderer) {
        m_logger->trace("Setting renderer");
        m_renderer = std::move(renderer);
    }
    void ModuleSet::set_core_event_handler(std::unique_ptr<event::ICoreEventHandler> core_event_handler) {
        m_logger->trace("Setting core event handler");
        m_core_event_handler = std::move(core_event_handler);
    }
    void ModuleSet::set_world(std::unique_ptr<engine::IEngine> world) {
        m_logger->trace("Setting world");
        m_world = std::move(world);
    }
    bool ModuleSet::check_modules(bool create_missing) {
        bool result = true;
        if (m_window == nullptr) {
            m_logger->error("Window is not set");
            result = false;
            if (create_missing) {
                m_logger->warn("Making default window");
                m_window = std::make_unique<window::IMainWindow>;
            }
        }

        return result;
    }
    void ModuleSet::initialise() {
        m_logger->trace("Initialising modules");
        m_window->initialise();
        m_renderer->initialise();
        m_core_event_handler->initialise();
        m_world->initialise();
    }
    void ModuleSet::configure() {
        m_logger->trace("Configuring modules");
        m_window->configure();
        m_renderer->configure();
        m_core_event_handler->configure();
        m_world->configure();
    }
    void ModuleSet::update() {}
    void ModuleSet::cleanup() {}
    void ModuleSet::on_quit() {
        m_logger->trace("Quitting modules");
        // m_window->on_quit();
        m_renderer->on_quit();
        m_core_event_handler->on_quit();
        m_world->on_quit();
    }
    ModuleSet::ModuleSet(ModuleSet&& other) noexcept = default;
    ModuleSet& ModuleSet::operator=(ModuleSet&& other) noexcept = default;
}
