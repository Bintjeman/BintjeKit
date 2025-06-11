/*!
 * @author bintjeman
 * @date 11.06.25
 * @name default_event_manager.cpp
 */

#include "bintjekit/event_manager/default_event_manager.hpp"
#include <vector>
#include <algorithm>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include "bintjekit/event_manager/event_listener.hpp"

namespace bnjkit {
    namespace event {
        DefaultEventManager::DefaultEventManager() = default;

        DefaultEventManager::~DefaultEventManager() = default;

        void DefaultEventManager::initialise() {
        }

        void DefaultEventManager::configure() {
        }

        void DefaultEventManager::register_listener(IEventListener *listener) {
            if (listener) {
                // Optionnel : vérifier les doublons
                if (std::find(m_listeners.begin(), m_listeners.end(), listener) == m_listeners.end()) {
                    m_listeners.push_back(listener);
                }
            }
        }
        void DefaultEventManager::unregister_listener(IEventListener *listener) {
            if (listener) {
                m_listeners.erase(
                    std::remove(m_listeners.begin(), m_listeners.end(), listener),
                    m_listeners.end()
                );
            }
        }
        void DefaultEventManager::process_events(sf::Window &window) {
            while (auto event = window.pollEvent()) {
                // Dispatch aux listeners
                for (auto *listener: m_listeners) {
                    listener->on_sfml_event(*event);
                }
                // Gestion spéciale si nécessaire
                if (event->is<sf::Event::Closed>()) {
                }
            }
        }
    } // event
} // bnjkit
