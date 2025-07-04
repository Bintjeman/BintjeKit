/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.cpp
 */
#include "bintjekit/core/core.hpp"
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/event_manager/event_manager.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/renderer/i_renderer.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/configuration/settings.hpp"
#include "bintjekit/configuration/utils.hpp"
#include "bintjekit/renderer/i_engine_renderer.hpp"
#include "bintjekit/utils/time/time.hpp"

namespace bnjkit::core {
    Core::Core() {
        m_logger = Logger::get_logger(module_names::CORE);
        m_logger->info("Constructor of Core");
#ifndef NDEBUG
        m_logger->critical("Running in debug mode");
#endif
    }
    Core::~Core() {
        m_logger->info("Destructor of Core");
        Logger::shutdown();
    }
    void Core::configure() {
        static_assert(!std::is_abstract_v<decltype(* m_engine)>,
                      "Engine class must implement all pure virtual methods");
        static_assert(!std::is_abstract_v<decltype(* m_engine_renderer)>,
                      "EngineRenderer class must implement all pure virtual methods");
        static_assert(!std::is_abstract_v<decltype(* m_renderer)>,
                      "Renderer class must implement all pure virtual methods");
        static_assert(!std::is_abstract_v<decltype(* m_imgui_renderer)>,
                      "ImGuiRenderer class must implement all pure virtual methods");

        m_logger->debug("Configuring Core");
        if (!m_settings) {
            m_logger->warn("No settings set. Using default settings");
            m_settings = std::make_shared<conf::Settings>();
        }
        // Settings
        m_event_manager->set_core_event_handler_settings(
            m_settings->create_child("/Event"_json_pointer));
        m_engine_renderer->set_settings(m_settings->create_child("/Renderer/Engine"_json_pointer));
        m_renderer->set_settings(m_settings->create_child("/Renderer"_json_pointer));
        m_imgui_renderer->set_settings(m_settings->create_child("/Renderer/ImGui"_json_pointer));
        m_main_window->set_settings(m_settings->create_child("/Window"_json_pointer));
        m_engine->set_settings(m_settings->create_child("/Engine"_json_pointer));
        // Custom settings
        m_engine->set_custom(
            m_settings->create_child(
                nlohmann::json::json_pointer(std::string("/" + m_engine->name()))));
        m_engine_renderer->set_custom(m_settings->create_child(
            nlohmann::json::json_pointer(std::string("/Renderer/" + m_engine_renderer->name()))));
        // Configure modules
        m_event_manager->configure();
        m_engine->configure();
        m_engine_renderer->configure();
        m_main_window->configure();
        m_renderer->configure();
        m_imgui_renderer->configure();
    }
    void Core::configure(const std::shared_ptr<conf::Settings>& settings) {
        m_logger->debug("Configuring Core from settings");
        set_settings(settings);
        configure();
    }
    void Core::configure(const std::filesystem::path& conf_file_path) {
        m_logger->debug("Configuring Core from file: {}", conf_file_path.string());
        std::shared_ptr<conf::Settings> settings = std::make_shared<conf::Settings>();
        settings->load_from_json(conf::from_file(conf_file_path));
        settings->set_path(conf_file_path);
        configure(settings);
    }
    void Core::run() {
        m_logger->info("Running Core");
        m_main_window->show();
        m_imgui_renderer->init();
        m_renderer->configure();
        while (m_main_window->isOpen()) {
            if (window_pulser()) {
                m_event_manager->process_events(* m_main_window);
                if (m_state == State::RUNNING && engine_pulser()) {
                    m_engine->update();
                }
                if (renderer_pulser()) {
                    m_imgui_renderer->update();
                    m_renderer->render();
                }
            }
        }
        m_logger->info("Core stopped");
        m_event_manager->on_quit();
        m_renderer->on_quit();
        m_engine->on_quit();
        m_engine_renderer->on_quit();
        m_imgui_renderer->on_quit();
    }
    conf::Settings& Core::settings() const {
        return * m_settings;
    }
    Core::State Core::state() const {
        return m_state;
    }
    engine::IEngine& Core::engine() {
        return * m_engine;
    }
    renderer::IRenderer& Core::renderer() {
        return * m_renderer;
    }
    renderer::IEngineRenderer& Core::engine_renderer() {
        return * m_engine_renderer;
    }
    renderer::IImGuiRenderer& Core::imgui_renderer() {
        return * m_imgui_renderer;
    }
    window::IMainWindow& Core::main_window() {
        return * m_main_window;
    }
    event::EventManager& Core::event_manager() {
        return * m_event_manager;
    }
    long Core::engine_frequency() {
        return engine_pulser.target_freqency();
    }
    long Core::renderer_frequency() {
        return renderer_pulser.target_freqency();
    }
    long Core::window_frequency() {
        return window_pulser.target_freqency();
    }
    long Core::engine_effective_frequency() {
        return engine_pulser.effective_frequency();
    }
    long Core::renderer_effective_frequency() {
        return renderer_pulser.effective_frequency();
    }
    long Core::window_effective_frequency() {
        return window_pulser.effective_frequency();
    }
    void Core::set_state(const State& state) {
        m_state = state;
    }
    void Core::set_modules(std::unique_ptr<window::IMainWindow> window,
                           std::unique_ptr<event::EventManager> event_manager,
                           std::unique_ptr<engine::IEngine> engine,
                           std::unique_ptr<renderer::IRenderer> renderer,
                           std::unique_ptr<renderer::IEngineRenderer> engine_renderer,
                           std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer
    ) {
        m_logger->debug("Setting modules");
        m_main_window = std::move(window);
        m_event_manager = std::move(event_manager);
        m_engine = std::move(engine);
        m_renderer = std::move(renderer);
        m_engine_renderer = std::move(engine_renderer);
        m_imgui_renderer = std::move(imgui_renderer);
    }
    void Core::set_engine_frequency(long frequency) {
        engine_pulser.set_frequency(frequency);
    }
    void Core::set_renderer_frequency(long frequency) {
        renderer_pulser.set_frequency(frequency);
    }
    void Core::set_window_frequency(long frequency) {
        window_pulser.set_frequency(frequency);
    }
    void Core::set_settings(const std::shared_ptr<conf::Settings>& settings) {
        m_settings = settings;
    }
    void Core::save_settings() {
        m_settings->save_to_file();
    }
    std::string Core::state_to_string(State state) {
        switch (state) {
            case State::RUNNING: return "RUNNING";
            case State::PAUSED: return "PAUSED";
            case State::STOPPED: return "STOPPED";
            default: return "UNKNOWN";
        }
    }
} // bnjkit
