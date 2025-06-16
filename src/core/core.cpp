/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.cpp
 */
#include "bintjekit/core/core.hpp"

#include "bintjekit/core/logger.hpp"
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/event_manager/i_event_manager.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/renderer/i_renderer.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/configuration/configuration_manager.hpp"
#include "bintjekit/renderer/i_engine_renderer.hpp"
namespace bnjkit::core {
    Core::Core() {
        m_logger = Logger::get_logger(module_names::CORE);
        m_logger = Logger::get_logger(module_names::CORE);
        m_logger->info("Constructor of Core");
        m_config_manager = std::make_shared<conf::ConfigurationManager>();
        m_config_manager->load_from_file("conf.json");
    }

    Core::~Core() {
        m_logger->info("Destructor of Core");
        Logger::shutdown();
    }

    void Core::set_modules(std::unique_ptr<window::IMainWindow> window,
                           std::unique_ptr<event::IEventManager> event_manager,
                           std::unique_ptr<engine::IEngine> engine,
                           std::unique_ptr<renderer::IRenderer> renderer,
                           std::unique_ptr<renderer::IEngineRenderer> engine_renderer,
                           std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer) {
        m_logger->info("Setting modules");
        m_main_window = std::move(window);
        m_event_manager = std::move(event_manager);
        m_engine = std::move(engine);
        m_renderer = std::move(renderer);
        m_engine_renderer = std::move(engine_renderer);
        m_imgui_renderer = std::move(imgui_renderer);
    }

    void Core::run() {
        m_logger->info("Running Core");
        m_main_window->show();
        m_imgui_renderer->init();
        m_renderer->configure();
        while (m_main_window->isOpen()) {
            m_event_manager->process_events(*m_main_window);
            if (m_state == State::RUNNING && engine_pulser()) {
                m_engine->update();
            }
            if (renderer_pulser()) {
                m_imgui_renderer->update();
                m_renderer->render();
            }
        }
        m_logger->info("Core stopped");
    }

    void Core::on_sfml_event(const sf::Event &event) {
        m_logger->debug("Core: on_sfml_event");
        auto shift [[maybe_unused]] = []() {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift) || sf::Keyboard::isKeyPressed(
                    sf::Keyboard::Key::LShift)) {
                return true;
            }
            return false;
        };
        if (const auto &key = event.getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Space) {
                m_logger->debug("Core: on_sfml_event: Space");
                pause_button();
            }
        }
    }

    void Core::pause_button() {
        switch (m_state) {
            case State::RUNNING:
                m_state = State::PAUSED;
                break;
            case State::PAUSED:
            case State::STOPPED:
                if (m_engine->state() == engine::IEngine::State::READY) {
                    m_state = State::RUNNING;
                }
                break;
            default:
                break;
        }
    }

    Core::State Core::state() const {
        return m_state;
    }

    std::string Core::state_to_string(State state) {
        switch (state) {
            case State::RUNNING:
                return "RUNNING";
            case State::PAUSED:
                return "PAUSED";
            case State::STOPPED:
                return "STOPPED";
            default:
                return "UNKNOWN";
        }
    }
} // bnjkit
