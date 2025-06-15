/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.cpp
 */

#include "bintjekit/event_manager/i_event_manager.hpp"
#include <algorithm>
#include <SFML/Window/Window.hpp>
#include <imgui-SFML.h>
#include "bintjekit/core/logger.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"
namespace bnjkit {
    namespace event {
        IEventManager::IEventManager() {
            m_logger = core::Logger::get_logger(core::module_names::EVENT);
            m_logger->info("Constructor of IEventManager");
        }

        IEventManager::~IEventManager() {
            m_logger->info("Destructor of IEventManager");
        }

        void IEventManager::set_imgui_renderer(renderer::IImGuiRenderer *renderer) {
            m_logger->info("Setting imgui renderer");
            m_imgui_renderer = renderer;
        }

        void IEventManager::process_events(sf::Window &window) {
            while (auto event = window.pollEvent()) {
                m_imgui_renderer->process_events(*event);
                for (auto *listener: m_listeners) {
                    listener->on_sfml_event(*event);
                }
                general_event(*event);
            }
        }

        void IEventManager::register_listener(IEventListener *listener) {
            m_logger->info("Registering listener");
            if (listener) {
                if (std::find(m_listeners.begin(), m_listeners.end(), listener) == m_listeners.end()) {
                    m_listeners.push_back(listener);
                }
            }
        }

        void IEventManager::unregister_listener(IEventListener *listener) {
            m_logger->info("Unregistering listener");
            auto it = std::remove(m_listeners.begin(), m_listeners.end(), listener);
            m_listeners.erase(it, m_listeners.end());
        }

        void IEventManager::general_event(const sf::Event &event) {
        }
    } // event
} // bnjkit
