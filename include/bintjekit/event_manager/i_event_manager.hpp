/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.hpp
 */
#ifndef I_EVENT_MANAGER_HPP
#define I_EVENT_MANAGER_HPP
#pragma once
#include <memory>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <spdlog/fwd.h>
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/renderer/i_bnjkit_imgui.hpp"


namespace sf {
    class Window;
}

namespace bnjkit {
    namespace renderer {
        class IImGuiRenderer;
    }

    namespace event {
        class ICoreEventHandler;
        class IEventListener;

        class IEventManager /*: public core::IModule*/ {
        public:
            IEventManager();
            ~IEventManager() /*override*/;
            void set_imgui_renderer(renderer::IImGuiRenderer *renderer);
            void set_core_event_handler(std::unique_ptr<ICoreEventHandler> core_event_handler);
            void process_events(sf::Window &window);
            void register_listener(IEventListener *listener);
            void unregister_listener(IEventListener *listener);

        protected:
            /*virtual*/ void general_event(const sf::Event &event);
            std::unique_ptr<ICoreEventHandler> m_core_event_handler;
            std::vector<IEventListener *> m_listeners;
            renderer::IImGuiRenderer *m_imgui_renderer;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // event
} // bnjkit
#endif //I_EVENT_MANAGER_HPP
