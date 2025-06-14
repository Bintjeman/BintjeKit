/*!
 * @author bintjeman
 * @date 11.06.25
 * @name default_event_manager.cpp
 */

#include "bintjekit/event_manager/default_event_manager.hpp"
#include <spdlog/logger.h>

namespace bnjkit {
    namespace event {
        DefaultEventManager::DefaultEventManager() : IEventManager() {
            m_logger->warn("Constructor of DefaultEventManager");
        }

        DefaultEventManager::~DefaultEventManager() {
            m_logger->warn("Destructor of DefaultEventManager");
        }

        void DefaultEventManager::initialise() {
            m_logger->warn("Initialising DefaultEventManager");
        }

        void DefaultEventManager::configure() {
            m_logger->warn("Configuring DefaultEventManager");
        }
    } // event
} // bnjkit
