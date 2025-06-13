/*!
 * @author bintjeman
 * @date 11.06.25
 * @name event_manager.cpp
 */

#include "event_manager.hpp"

namespace usr {
    EventManager::~EventManager() = default;

    void EventManager::initialise() {
        IEventManager::initialise();
    }

    void EventManager::configure() {
        IEventManager::configure();
    }
} // usr
