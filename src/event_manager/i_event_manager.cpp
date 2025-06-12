/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.cpp
 */

#include "bintjekit/event_manager/i_event_manager.hpp"
#include <algorithm>

namespace bnjkit {
    namespace event {
        IEventManager::IEventManager() {
        }

        IEventManager::~IEventManager() {
        }

        void IEventManager::initialise() {
            IModule::initialise();
        }

        void IEventManager::configure() {
            IModule::configure();
        }

        void IEventManager::process_events(sf::Window &window) {
        }

        void IEventManager::register_listener(IEventListener *listener) {
            if (listener) {
                if (std::find(m_listeners.begin(), m_listeners.end(), listener) == m_listeners.end()) {
                    m_listeners.push_back(listener);
                }
            }
        }

        void IEventManager::unregister_listener(IEventListener *listener) {
            auto it = std::remove(m_listeners.begin(), m_listeners.end(), listener);
            m_listeners.erase(it, m_listeners.end());
        }

        void IEventManager::general_event(const sf::Event &event) {

        }
    } // event
} // bnjkit
