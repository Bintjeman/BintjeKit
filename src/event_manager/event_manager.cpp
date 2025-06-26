/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.cpp
 */

#include "bintjekit/event_manager/event_manager.hpp"
#include <algorithm>
#include <SFML/Window/Window.hpp>
#include <imgui-SFML.h>
#include "../../include/bintjekit/logger/logger.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"
#include "bintjekit/event_manager/i_core_event_handler.hpp"
#include "bintjekit/renderer/i_bnjkit_imgui.hpp"

namespace bnjkit {
    namespace event {
        EventManager::EventManager() {
            m_logger = core::Logger::get_logger(core::module_names::EVENT);
            m_logger->info("Constructor of IEventManager");
        }

        EventManager::~EventManager() {
            m_logger->info("Destructor of IEventManager");
        }

        void EventManager::set_imgui_renderer(renderer::IImGuiRenderer *renderer) {
            m_logger->info("Setting imgui renderer");
            m_imgui_renderer = renderer;
        }

        void EventManager::set_core_event_handler(std::unique_ptr<ICoreEventHandler> core_event_handler) {
            m_logger->info("Setting core event handler");
            m_core_event_handler = std::move(core_event_handler);
        }

        void EventManager::process_events(sf::Window &window) {
            while (auto event = window.pollEvent()) {
                m_imgui_renderer->process_events(*event);
                for (auto *listener: m_listeners) {
                    listener->on_sfml_event(*event);
                }
                m_logger->trace("Processing events");
                m_core_event_handler->on_sfml_event(*event);
                general_event(*event);
            }
        }

        void EventManager::register_listener(IEventListener *listener) {
            m_logger->info("Registering listener");
            if (listener) {
                if (std::find(m_listeners.begin(), m_listeners.end(), listener) == m_listeners.end()) {
                    m_listeners.push_back(listener);
                }
            }
        }

        void EventManager::unregister_listener(IEventListener *listener) {
            m_logger->info("Unregistering listener");
            auto it = std::remove(m_listeners.begin(), m_listeners.end(), listener);
            m_listeners.erase(it, m_listeners.end());
        }

        void EventManager::general_event(const sf::Event &event[[maybe_unused]]) {
            m_logger->trace("General event");
        }
    } // event
} // bnjkit
