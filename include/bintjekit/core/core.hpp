/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.hpp
 */
#ifndef CORE_HPP
#define CORE_HPP
#pragma once
#include <memory>
#include <time/time.hpp>
#include <spdlog/fwd.h>
#include "bintjekit/event_manager/i_event_listener.hpp"

namespace bnjkit {
    namespace window {
        class IMainWindow;
    } // window
    namespace event {
        class IEventManager;
    } // event
    namespace engine {
        class IEngine;
    } // engine
    namespace renderer {
        class IEngineRenderer;
        class IRenderer;
        class IImGuiRenderer;
    } // renderer
    namespace conf {
        class ConfigurationManager;
    } // conf
    namespace core {
        class Core : public event::IEventListener {
        public:
            enum class State {
                RUNNING,
                PAUSED,
                STOPPED
            };

            Core();
            ~Core();
            void set_modules(std::unique_ptr<window::IMainWindow> window,
                             std::unique_ptr<event::IEventManager> event_manager,
                             std::unique_ptr<engine::IEngine> engine,
                             std::unique_ptr<renderer::IRenderer> renderer,
                             std::unique_ptr<renderer::IEngineRenderer> engine_renderer,
                             std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer);

            void run();
            void on_sfml_event(const sf::Event &event) override;
            void pause_button();

        private:
            State m_state{State::STOPPED};
            time::Pulser engine_pulser;
            time::Pulser renderer_pulser;
            time::Pulser window_pulser;
            std::unique_ptr<window::IMainWindow> m_main_window;
            std::unique_ptr<event::IEventManager> m_event_manager;
            std::unique_ptr<renderer::IRenderer> m_renderer;
            std::unique_ptr<engine::IEngine> m_engine;
            std::unique_ptr<renderer::IEngineRenderer> m_engine_renderer;
            std::unique_ptr<renderer::IImGuiRenderer> m_imgui_renderer;
            std::shared_ptr<conf::ConfigurationManager> m_config_manager;
            std::shared_ptr<spdlog::logger> m_logger;

        public:
            Core(const Core &) = delete;
            Core &operator=(const Core &) = delete;
            static std::string state_to_string(State state);
        };
    } // core
} // bnjkit
#endif //CORE_HPP
