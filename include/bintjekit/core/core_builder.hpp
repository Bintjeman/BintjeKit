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
    namespace core {
        class Core;

        /**
         * @class CoreBuilder
         * @brief A builder class for constructing a Core instance with configurable modules.
         *
         * The CoreBuilder class allows the construction of a Core object by setting
         * different modules, such as window, event manager, engine, renderer, and engine renderer.
         * Users can configure the Core instance by using the `set` methods or providing modules
         * explicitly via setter functions before finalizing the configuration with the `build` method.
         */
        class CoreBuilder {
        public:
            CoreBuilder();
            ~CoreBuilder();

            template<typename T>
            /**
             * @brief Sets the module of a specific type for the CoreBuilder.
             *
             * Depending on the template type `T`, this method initializes and assigns the corresponding
             * module to the CoreBuilder. The supported modules are:
             * - Window (derived from `window::IMainWindow`)
             * - Event Manager (derived from `event::IEventManager`)
             * - Engine (derived from `engine::IEngine`)
             * - Renderer (derived from `renderer::IRenderer`)
             * - Engine Renderer (derived from `renderer::IEngineRenderer`)
             *
             * @tparam T The type of the module to be set. Must derive from one of the supported base module types.
             * @return A reference to the CoreBuilder instance, allowing method chaining.
             */
            CoreBuilder &set() {
                if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
                    m_window = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<event::IEventManager, T>) {
                    m_event_manager = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
                    m_engine = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<renderer::IRenderer, T>) {
                    m_renderer = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<renderer::IEngineRenderer, T>) {
                    m_engine_renderer = std::make_unique<T>();
                } else if constexpr (std::is_base_of_v<renderer::IImGuiRenderer, T>) {
                    m_imgui_renderer = std::make_unique<T>();
                }
                return *this;
            }

            // template<typename T, typename... Args>
            /**
             * @brief Sets the module of a specific type with given parameters for the CoreBuilder.
             *
             * Allows initializing and assigning a specific module of type `T` with additional
             * arguments. This method is useful when construction of the module requires custom
             * parameters. The module must derive from one of the supported base module types.
             *
             * @tparam T The type of the module to be set. Must derive from a supported base module type.
             * @tparam Args The types of additional arguments for constructing the module.
             * @param args The arguments to be forwarded to the module's constructor.
             * @return A reference to the CoreBuilder instance, allowing method chaining.
             */
            // CoreBuilder &set(Args &&... args) {
            //     if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
            //         m_window = std::make_unique<T>(std::forward<Args>(args)...);
            //     }
            //     return *this;
            // }

            CoreBuilder &set_window_module(std::unique_ptr<window::IMainWindow> window);
            CoreBuilder &set_event_manager_module(std::unique_ptr<event::IEventManager> event_manager);
            CoreBuilder &set_engine_module(std::unique_ptr<engine::IEngine> engine);
            CoreBuilder &set_renderer_module(std::unique_ptr<renderer::IRenderer> renderer);
            CoreBuilder &set_engine_renderer(std::unique_ptr<renderer::IEngineRenderer> engine_renderer);
            CoreBuilder &set_imgui_renderer(std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer);
            /**
             * @brief Constructs and returns a fully configured Core instance.
             *
             * The `build` method creates a Core object by assembling and configuring its essential
             * modules, such as the main window, event manager, engine, renderer, and engine renderer.
             * If any modules are not explicitly set, default implementations are automatically created.
             * These modules are initialized and linked together appropriately to ensure proper functionality.
             *
             * @return A unique pointer to a fully configured Core instance.
             */
            std::unique_ptr<Core> build();

        private:
            std::unique_ptr<window::IMainWindow> m_window;
            std::unique_ptr<event::IEventManager> m_event_manager;
            std::unique_ptr<renderer::IRenderer> m_renderer;
            std::unique_ptr<engine::IEngine> m_engine;
            std::unique_ptr<renderer::IEngineRenderer> m_engine_renderer;
            std::shared_ptr<spdlog::logger> m_logger;
            std::unique_ptr<renderer::IImGuiRenderer> m_imgui_renderer;
        };
    } // core
} // bnjkit
#endif //CORE_BUILDER_HPP
