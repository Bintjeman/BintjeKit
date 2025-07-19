/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.cpp
 */
#include "bintjekit/core/core.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/configuration.hpp"
#include "bintjekit/core/modules.hpp"
#include "bintjekit/core/module_set.hpp"

namespace bnjkit::core {
    Core::Core() {
        m_logger = logger::Logger::get_logger(literals::logger::CORE);
        m_logger->info("Constructor of Core");
#ifndef NDEBUG
        m_logger->critical("Running in debug mode");
#endif
    }
    Core::~Core() {
        m_logger->info("Destructor of Core");
        logger::Logger::shutdown();
    }
    void Core::initialise() {
        m_logger->debug("Initialising Core");
        m_modules->initialise();
        m_initialized = true;
    }
    void Core::configure() {
        m_logger->debug("Configuring Core");
        if (!m_settings) {
            m_logger->warn("No settings set. Using default settings");
            m_settings = std::make_unique<conf::Settings>();
        }
        // Settings
        m_modules->window().set_settings(m_settings->create_child("/Window"_json_pointer));
        m_modules->event_manager().set_settings(m_settings->create_child("/EventManager"_json_pointer));
        m_modules->engine().set_settings(m_settings->create_child("/Engine"_json_pointer));
        m_modules->renderer().set_settings(m_settings->create_child("/Renderer"_json_pointer));
        m_modules->imgui_renderer().set_settings(m_settings->create_child("/ImGuiRenderer"_json_pointer));
        // Configure modules
        m_modules->configure();
        m_configured = true;
    }
    void Core::configure(const std::shared_ptr<conf::Settings>& settings) {
        m_logger->trace("Configuring Core from settings");
        set_settings(settings);
        configure();
    }
    void Core::configure(const std::filesystem::path& conf_file_path) {
        m_logger->trace("Configuring Core from file: {}", conf_file_path.string());
        const auto settings = std::make_shared<conf::Settings>();
        settings->load_from_json(conf::from_file(conf_file_path));
        settings->set_path(conf_file_path);
        configure(settings);
    }
    void Core::run() {
        m_logger->info("Running Core");
        if (!m_initialized) {
            m_logger->warn("Core not initialised");
            initialise();
        }
        if (!m_configured) {
            m_logger->warn("Core not configured");
            configure();
        }
        auto& window = m_modules->window();
        window.show();
        while (window.is_running()) {
            auto& engine = m_modules->engine();
            auto& renderer = m_modules->renderer();
            auto& imgui_renderer = m_modules->imgui_renderer();
            auto& event_manager = m_modules->event_manager();
            if (m_window_pulser()) {
                event_manager.process_events();
                if (m_state == State::RUNNING && m_engine_pulser()) {
                    engine.update();
                }
                if (m_renderer_pulser()) {
                    imgui_renderer.update();
                    renderer.render();
                }
            }
        }
        m_modules->on_quit();
        window.close();
        m_logger->info("Core stopped");
    }
    Core::State Core::state() const {
        return m_state;
    }
    conf::Settings& Core::settings() const {
        return * m_settings;
    }
    long Core::engine_frequency() const {
        return m_engine_pulser.target_freqency();
    }
    long Core::renderer_frequency() const {
        return m_renderer_pulser.target_freqency();
    }
    long Core::window_frequency() const {
        return m_window_pulser.target_freqency();
    }
    long Core::engine_effective_frequency() const {
        return m_engine_pulser.effective_frequency();
    }
    long Core::renderer_effective_frequency() const {
        return m_renderer_pulser.effective_frequency();
    }
    long Core::window_effective_frequency() const {
        return m_window_pulser.effective_frequency();
    }
    void Core::set_modules(std::unique_ptr<ModuleSet> modules) {
        m_logger->trace("Setting modules");
        m_modules = std::move(modules);
        // m_modules.set_modules();
    }
    void Core::set_state(const State& state) {
        m_state = state;
    }
    void Core::set_engine_frequency(const long frequency) {
        m_engine_pulser.set_frequency(frequency);
    }
    void Core::set_renderer_frequency(const long frequency) {
        m_renderer_pulser.set_frequency(frequency);
    }
    void Core::set_window_frequency(const long frequency) {
        m_window_pulser.set_frequency(frequency);
    }
    void Core::set_settings(const std::shared_ptr<conf::Settings>& settings) {
        m_settings = settings;
    }
    void Core::save_settings() const {
        m_settings->save_to_file();
    }
    std::string Core::state_to_string(const State state) {
        switch (state) {
            case State::RUNNING: return "RUNNING";
            case State::PAUSED: return "PAUSED";
            case State::STOPPED: return "STOPPED";
            default: return "UNKNOWN";
        }
    }
} // bnjkit
