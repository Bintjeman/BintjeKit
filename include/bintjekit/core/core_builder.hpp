/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.hpp
 */
#ifndef CORE_BUILDER_HPP
#define CORE_BUILDER_HPP
#pragma once
#include <memory>
#include <spdlog/fwd.h>

namespace bnjkit {
    namespace window {
        class IMainWindow;
    } // window
    namespace event {
        class EventManager;
        class ICoreEventHandler;
    } // event
    namespace engine {
        class IEngine;
    } // engine
    namespace renderer {
        class IEngineRenderer;
        class IRenderer;
        class IImGuiRenderer;
    } // renderer
    namespace core {
        class Core;

        class CoreBuilder {
        public:
            CoreBuilder();
            ~CoreBuilder();

            template<typename T>
            CoreBuilder &set() {
                if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
                    m_window = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<event::EventManager, T>) {
                    m_event_manager = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
                    m_engine = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<renderer::IRenderer, T>) {
                    m_renderer = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<renderer::IEngineRenderer, T>) {
                    m_engine_renderer = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<renderer::IImGuiRenderer, T>) {
                    m_imgui_renderer = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<event::ICoreEventHandler, T>) {
                    m_core_event_handler = std::make_unique<T>();
                }
                return *this;
            }

            // template<typename T, typename... Args>
            // CoreBuilder &set(Args &&... args) {
            //     if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
            //         m_window = std::make_unique<T>(std::forward<Args>(args)...);
            //     }
            //     return *this;
            // }

            CoreBuilder &set_window_module(std::unique_ptr<window::IMainWindow> window);
            CoreBuilder &set_event_manager_module(std::unique_ptr<event::EventManager> event_manager);
            CoreBuilder &set_engine_module(std::unique_ptr<engine::IEngine> engine);
            CoreBuilder &set_renderer_module(std::unique_ptr<renderer::IRenderer> renderer);
            CoreBuilder &set_engine_renderer(std::unique_ptr<renderer::IEngineRenderer> engine_renderer);
            CoreBuilder &set_imgui_renderer(std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer);
            CoreBuilder &set_core_event_handler(std::unique_ptr<event::ICoreEventHandler> core_event_handler);
            std::unique_ptr<Core> build();

        private:
            std::unique_ptr<window::IMainWindow> m_window;
            std::unique_ptr<event::EventManager> m_event_manager;
            std::unique_ptr<renderer::IRenderer> m_renderer;
            std::unique_ptr<engine::IEngine> m_engine;
            std::unique_ptr<renderer::IEngineRenderer> m_engine_renderer;
            std::shared_ptr<spdlog::logger> m_logger;
            std::unique_ptr<renderer::IImGuiRenderer> m_imgui_renderer;
            std::unique_ptr<event::ICoreEventHandler> m_core_event_handler;
        };
    } // core
} // bnjkit
#endif //CORE_BUILDER_HPP
