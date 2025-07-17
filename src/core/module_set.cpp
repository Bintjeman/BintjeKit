/*!
 * @author bintjeman
 * @date 16.07.25
 * @name module_set.cpp
 */
#include "bintjekit/core/module_set.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/core/modules.hpp"
#include "bintjekit/core/default_modules.hpp"
namespace bnjkit::core {
    ModuleSet::ModuleSet() {
        m_logger = Logger::get_logger(literals::logger::CORE);
        m_logger->info("Constructor of ModuleSet");
    }
    ModuleSet::~ModuleSet() {
        // m_logger->info("Destructor of ModuleSet");
    }
    window::IMainWindow& ModuleSet::window() {
        return * m_window;
    }
    engine::IEngine& ModuleSet::engine() {
        return * m_engine;
    }
    event::IEventManager& ModuleSet::event_manager() {
        return * m_event_manager;
    }
    renderer::IRenderer& ModuleSet::renderer() {
        return * m_renderer;
    }
    renderer::IImGuiRenderer& ModuleSet::imgui_renderer() {
        return * m_imgui_renderer;
    }
    window::IMainWindow& ModuleSet::window() const {
        return * m_window;
    }
    engine::IEngine& ModuleSet::engine() const {
        return * m_engine;
    }
    event::IEventManager& ModuleSet::event_manager() const {
        return * m_event_manager;
    }
    renderer::IRenderer& ModuleSet::renderer() const {
        return * m_renderer;
    }
    renderer::IImGuiRenderer& ModuleSet::imgui_renderer() const {
        return * m_imgui_renderer;
    }
    void ModuleSet::set_window(std::unique_ptr<window::IMainWindow> window) {
        m_logger->trace("Setting window");
        m_window = std::move(window);
    }
    void ModuleSet::set_engine(std::unique_ptr<engine::IEngine> engine) {
        m_logger->trace("Setting world");
        m_engine = std::move(engine);
    }
    void ModuleSet::set_event_manager(std::unique_ptr<event::IEventManager> event_manager) {
        m_logger->trace("Setting event manager");
        m_event_manager = std::move(event_manager);
    }
    void ModuleSet::set_renderer(std::unique_ptr<renderer::IRenderer> renderer) {
        m_logger->trace("Setting renderer");
        m_renderer = std::move(renderer);
    }
    void ModuleSet::set_imgui_renderer(std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer) {
        m_logger->trace("Setting imgui renderer");
        m_imgui_renderer = std::move(imgui_renderer);
    }
    bool ModuleSet::check_modules(bool create_missing) {
        bool result = true;
        if (m_window == nullptr) {
            m_logger->error("Window is not set");
            result = false;
            if (create_missing) {
                m_logger->warn("Making default window");
                m_window = std::make_unique<window::DefaultMainWindow>();
            }
        }
        if (m_event_manager == nullptr) {
            m_logger->error("Event manager is not set");
            result = false;
            if (create_missing) {
                m_logger->warn("Making default event manager");
                m_event_manager = std::make_unique<event::IEventManager>();
            }
        }
        if (m_engine == nullptr) {
            m_logger->error("Engine is not set");
            result = false;
            if (create_missing) {
                m_logger->warn("Making default engine");
                m_engine = std::make_unique<engine::DefaultEngine>();
            }
        }
        if (m_renderer == nullptr) {
            m_logger->error("Renderer is not set");
            result = false;
            if (create_missing) {
                m_logger->warn("Making default renderer");
                m_renderer = std::make_unique<renderer::DefaultRenderer>();
            }
        }
        if (m_imgui_renderer == nullptr) {
            m_logger->error("ImGui renderer is not set");
            result = false;
            if (create_missing) {
                m_logger->warn("Making default imgui renderer");
                m_imgui_renderer = std::make_unique<renderer::IImGuiRenderer>();
            }
        }
        return result;
    }

    void ModuleSet::initialise() {
        m_logger->trace("Initialising modules");
        m_window->initialise();
        m_event_manager->initialise();
        m_engine->initialise();
        m_renderer->initialise();
        m_imgui_renderer->initialise();
    }

    void ModuleSet::configure() {
        m_logger->trace("Configuring modules");
        m_window->configure();
        m_engine->configure();
        m_engine->configure();
        m_event_manager->configure();
        m_renderer->configure();
        m_imgui_renderer->configure();
    }

    void ModuleSet::update() {}

    void ModuleSet::cleanup() {}

    void ModuleSet::on_quit() {
        m_logger->trace("Quitting modules");
        // m_window->on_quit();
        m_event_manager->on_quit();
        m_engine->on_quit();
        m_renderer->on_quit();
        m_imgui_renderer->on_quit();
    }

    ModuleSet::ModuleSet(ModuleSet&& other) noexcept = default;
    ModuleSet& ModuleSet::operator=(ModuleSet&& other) noexcept = default;
}
