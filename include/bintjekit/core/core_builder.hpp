/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.hpp
 */
#ifndef CORE_BUILDER_HPP
#define CORE_BUILDER_HPP
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
        class IRenderer;
    } // renderer
    namespace core {
        class Core;

        class CoreBuilder {
        public:
            CoreBuilder();
            ~CoreBuilder();
            CoreBuilder &set_window_module(std::unique_ptr<window::IMainWindow> window);
            CoreBuilder &set_event_manager_module(std::unique_ptr<event::IEventManager> event_manager);
            std::unique_ptr<Core> build();

        private:
            std::unique_ptr<window::IMainWindow> m_window;
            std::unique_ptr<event::IEventManager> m_event_manager;
            std::unique_ptr<renderer::IRenderer> m_renderer;
            std::unique_ptr<engine::IEngine> m_engine;
        };
    } // core
} // bnjkit
#endif //CORE_BUILDER_HPP
