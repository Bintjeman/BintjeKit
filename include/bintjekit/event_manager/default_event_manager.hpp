/*!
 * @author bintjeman
 * @date 11.06.25
 * @name default_event_manager.hpp
 */
#ifndef DEFAULT_EVENT_MANAGER_HPP
#define DEFAULT_EVENT_MANAGER_HPP
#pragma once
#include "i_event_manager.hpp"

namespace bnjkit {
    namespace event {
        /**
         * @class DefaultEventManager
         * @brief Implements the IEventManager interface to handle event management.
         *
         * The DefaultEventManager is responsible for managing event listeners
         * and processing events as part of the system's event-handling mechanism.
         * It provides initialization and configuration functionalities required
         * for the event management module.
         */
        class DefaultEventManager : public IEventManager {
        public:
            DefaultEventManager();
            ~DefaultEventManager() override;
            void initialise() override;
            void configure() override;
        };
    } // event
} // bnjkit
#endif //DEFAULT_EVENT_MANAGER_HPP
