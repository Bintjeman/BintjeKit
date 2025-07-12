/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.hpp
 */
#ifndef BNJKIT_CORE_CORE_HPP
#define BNJKIT_CORE_CORE_HPP
#pragma once
#include <filesystem>
#include <memory>
#include <spdlog/fwd.h>
#include "bintjekit/utils/time/time.hpp"
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
        class Core {
        public:
            enum class State {
                RUNNING,
                PAUSED,
                STOPPED
            };

            Core();
            ~Core();
            void configure();
            void configure(const std::shared_ptr<conf::Settings>& settings);
            void configure(const std::filesystem::path& conf_file_path);
            void run();
            [[nodiscard]] conf::Settings& settings() const;
            [[nodiscard]] State state() const;
            [[nodiscard]] engine::IEngine& engine() const;
            [[nodiscard]] renderer::IRenderer& renderer() const;
            [[nodiscard]] renderer::IEngineRenderer& engine_renderer() const;
            [[nodiscard]] renderer::IImGuiRenderer& imgui_renderer() const;
            [[nodiscard]] window::IMainWindow& main_window() const;
            [[nodiscard]] event::EventManager& event_manager() const;
            [[nodiscard]] long engine_frequency() const;
            [[nodiscard]] long renderer_frequency() const;
            [[nodiscard]] long window_frequency() const;
            [[nodiscard]] long engine_effective_frequency() const;
            [[nodiscard]] long renderer_effective_frequency() const;
            [[nodiscard]] long window_effective_frequency() const;
            void set_state(const State& state);
            void set_modules(std::unique_ptr<window::IMainWindow> window,
                             std::unique_ptr<event::EventManager> event_manager,
                             std::unique_ptr<engine::IEngine> engine,
                             std::unique_ptr<renderer::IRenderer> renderer,
                             std::unique_ptr<renderer::IEngineRenderer> engine_renderer,
                             std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer
            );
            void set_engine_frequency(long frequency);
            void set_renderer_frequency(long frequency);
            void set_window_frequency(long frequency);
            void set_settings(const std::shared_ptr<conf::Settings>& settings);
            void save_settings();

        protected:
            State m_state{State::STOPPED};
            utils::time::Pulser m_engine_pulser;
            utils::time::Pulser m_renderer_pulser;
            utils::time::Pulser m_window_pulser;

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
            Core(const Core&) = delete;
            Core& operator=(const Core&) = delete;
            static std::string state_to_string(State state);
        };
    } // core
} // bnjkit
#endif //BNJKIT_CORE_CORE_HPP
