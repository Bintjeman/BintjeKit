/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.hpp
 */
#ifndef BNJKIT_EVENT_I_EVENT_MANAGER_HPP
#define BNJKIT_EVENT_I_EVENT_MANAGER_HPP
#pragma once
#include <memory>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <spdlog/fwd.h>

#include "bintjekit/configuration/node.hpp"

namespace sf {
    class Window;
}

namespace bnjkit {
    namespace conf {
        class Node;
    }
    namespace renderer {
        class IImGuiRenderer;
    }

    namespace event {
        class ICoreEventHandler;
        class IEventListener;

        class EventManager {
        public:
            EventManager();
            ~EventManager();
            void set_imgui_renderer(renderer::IImGuiRenderer* renderer);
            void set_core_event_handler(std::shared_ptr<ICoreEventHandler> core_event_handler);
            void process_events(sf::Window& window);
            void register_listener(IEventListener* listener);
            void unregister_listener(IEventListener* listener);
            void set_core_event_handler_settings(const conf::Node& settings);
            void set_core_event_handler_custom_settings(const conf::Node& settings);
            [[nodiscard]] ICoreEventHandler* get_core_event_handler() const;
            void configure() ;
            void on_quit() ;
        protected:
            void general_event(const sf::Event& event) const;
            std::shared_ptr<ICoreEventHandler> m_core_event_handler;
            std::vector<IEventListener*> m_listeners;
            renderer::IImGuiRenderer* m_imgui_renderer;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // event
} // bnjkit
#endif // BNJKIT_EVENT_I_EVENT_MANAGER_HPP
