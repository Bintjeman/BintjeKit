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
#include "bintjekit/event_manager/i_event_listener.hpp"

namespace bnjkit {
    namespace event {
        DefaultEventManager::DefaultEventManager() = default;

        DefaultEventManager::~DefaultEventManager() = default;

        void DefaultEventManager::initialise() {
        }

        void DefaultEventManager::configure() {
        }

    } // event
} // bnjkit
