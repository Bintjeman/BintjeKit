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
namespace bnjkit {
    namespace window {
        class IMainWindow;
    } // window
    namespace event {
        class EventManager;
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
        class Settings;
    } // conf
    namespace core {
        /**
         *
         */
        class Core {
        public:

            enum class State {
                RUNNING,
                PAUSED,
                STOPPED
            };

            Core();
            ~Core();
            void set_modules(std::unique_ptr<window::IMainWindow> window,
                             std::unique_ptr<event::EventManager> event_manager,
                             std::unique_ptr<engine::IEngine> engine,
                             std::unique_ptr<renderer::IRenderer> renderer,
                             std::unique_ptr<renderer::IEngineRenderer> engine_renderer,
                             std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer);

            void run();
            [[nodiscard]] conf::Settings& settings() const;
            [[nodiscard]] State state() const;
            [[nodiscard]] long engine_frequency();
            [[nodiscard]] long renderer_frequency();
            [[nodiscard]] long window_frequency();
            [[nodiscard]] long engine_effective_frequency();
            [[nodiscard]] long renderer_effective_frequency();
            [[nodiscard]] long window_effective_frequency();
            void set_state(const State& state);
            void set_engine_frequency(long frequency);
            void set_renderer_frequency(long frequency);
            void set_window_frequency(long frequency);

        protected:
            State m_state{State::STOPPED};
            time::Pulser engine_pulser;
            time::Pulser renderer_pulser;
            time::Pulser window_pulser;

        private:
            std::unique_ptr<window::IMainWindow> m_main_window;
            std::unique_ptr<event::EventManager> m_event_manager;
            std::unique_ptr<renderer::IRenderer> m_renderer;
            std::unique_ptr<engine::IEngine> m_engine;
            std::unique_ptr<renderer::IEngineRenderer> m_engine_renderer;
            std::unique_ptr<renderer::IImGuiRenderer> m_imgui_renderer;
            std::shared_ptr<conf::Settings> m_settings;
            std::shared_ptr<spdlog::logger> m_logger;

        public:
            Core(const Core &) = delete;
            Core &operator=(const Core &) = delete;
            static std::string state_to_string(State state);
        };
    } // core
} // bnjkit
#endif //CORE_HPP
