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
    } // renderer
    namespace core {
        /**
         * @class Core
         * @brief Represents the core management class responsible for integrating and managing essential system components.
         *
         * The Core class encapsulates functionality to manage the primary components
         * of the system, including the window, event manager, engine, renderer, and engine renderer.
         * It operates as the central entity where these modules are initialized, integrated, and executed.
         * This class ensures that all modules are properly connected and runs the main application loop.
         */
        class Core {
        public:
            Core();
            ~Core();
            /**
             * @brief Sets the core system modules required for the main application to function.
             *
             * This method initializes and assigns the essential modules to the core system.
             * The provided modules include the main window, event manager, engine, renderer,
             * and engine renderer, all of which will be utilized in the application lifecycle.
             *
             * @param window A unique pointer to an instance of IMainWindow representing the main application window.
             * @param event_manager A unique pointer to an instance of IEventManager responsible for managing events.
             * @param engine A unique pointer to an instance of IEngine to manage the application engine.
             * @param renderer A unique pointer to an instance of IRenderer for rendering operations.
             * @param engine_renderer A unique pointer to an instance of IEngineRenderer for rendering engine-related components.
             */
            void set_modules(std::unique_ptr<window::IMainWindow> window,
                             std::unique_ptr<event::IEventManager> event_manager,
                             std::unique_ptr<engine::IEngine> engine,
                             std::unique_ptr<renderer::IRenderer> renderer,
                             std::unique_ptr<renderer::IEngineRenderer> engine_renderer);

            /**
             * @brief Executes the main application loop, managing system modules to ensure continuous functionality.
             *
             * The `run` method initializes the primary operations of the application by
             * starting the main loop. It ensures that the application window is displayed,
             * events are processed, and the engine and renderer operate in tandem until the
             * window is closed. It facilitates interaction among all integrated core modules.
             *
             * This method is essential for coordinating the functionality of the window,
             * event management, engine updates, and rendering pipeline in a synchronized manner.
             */
            void run();

        private:
            bnjkit::time::Pulser engine_pulser;
            bnjkit::time::Pulser renderer_pulser;
            bnjkit::time::Pulser window_pulser;
            std::unique_ptr<window::IMainWindow> m_main_window;
            std::unique_ptr<event::IEventManager> m_event_manager;
            std::unique_ptr<renderer::IRenderer> m_renderer;
            std::unique_ptr<engine::IEngine> m_engine;
            std::unique_ptr<renderer::IEngineRenderer> m_engine_renderer;

        public:
            Core(const Core &) = delete;
            Core &operator=(const Core &) = delete;
        };
    } // core
} // bnjkit
#endif //CORE_HPP
