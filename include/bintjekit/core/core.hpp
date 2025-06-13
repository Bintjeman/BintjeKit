/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.hpp
 */
#ifndef CORE_HPP
#define CORE_HPP
#pragma once
#include <memory>

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
        class Core {
        public:
            Core();
            ~Core();
            void set_modules(std::unique_ptr<window::IMainWindow> window,
                             std::unique_ptr<event::IEventManager> event_manager,
                             std::unique_ptr<engine::IEngine> engine,
                             std::unique_ptr<renderer::IRenderer> renderer,
                             std::unique_ptr<renderer::IEngineRenderer> engine_renderer);
            void run();

        private:
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
