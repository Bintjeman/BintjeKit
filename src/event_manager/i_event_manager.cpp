/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.cpp
 */

#include "bintjekit/event_manager/i_event_manager.hpp"

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

} // event
} // bnjkit