/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.hpp
 */
#ifndef I_EVENT_MANAGER_HPP
#define I_EVENT_MANAGER_HPP
#pragma once
#include <vector>
#include "bintjekit/core/i_module.hpp"
#include "SFML/Window/Event.hpp"

namespace sf {
    class Window;
}

namespace bnjkit {
    namespace event {
        class IEventListener ;
        // class IEvent;

        /**
         * @class IEventManager
         * @brief Interface for managing event handling in the system.
         *
         * The IEventManager class is responsible for managing events and notifying
         * registered listeners about specific events. It serves as a crucial module
         * in the system's event-handling infrastructure. This class also provides
         * methods for initialization and configuration as part of the module interface.
         *
         * In addition to its core functionality, IEventManager maintains a collection
         * of event listeners and supports operations to register and unregister them.
         */
        class IEventManager : public core::IModule {
        public:
            IEventManager();
            ~IEventManager() override;
            /**
             * @brief Processes incoming events from the SFML window and notifies listeners.
             *
             * This method handles event polling from the specified SFML window, dispatches
             * events to all registered listeners, and invokes general event handling logic.
             * It ensures that each event is propagated appropriately to maintain system
             * responsiveness and functionality.
             *
             * @param window A reference to the SFML window from which events are polled.
             */
            void process_events(sf::Window &window);
            /**
             * @brief Registers an event listener to receive event notifications.
             *
             * This method adds the specified listener to the internal collection of event
             * listeners maintained by the event manager. The registered listener will be
             * notified of events dispatched by the system, enabling it to handle and
             * respond to relevant events. If the listener is already registered, it is
             * not added again.
             *
             * @param listener A pointer to the IEventListener instance to be registered.
             *                 The listener must implement the required event handling
             *                 interface.
             */
            void register_listener(IEventListener *listener);
            /**
             * @brief Unregisters an event listener from receiving event notifications.
             *
             * This method removes the specified listener from the internal collection of event
             * listeners maintained by the event manager. Once unregistered, the listener will
             * no longer be notified of events dispatched by the system. If the listener is not
             * found in the collection, no action is taken.
             *
             * @param listener A pointer to the IEventListener instance to be unregistered.
             *                 The listener should have been previously registered.
             */
            void unregister_listener(IEventListener *listener);
            /**
             * @brief Handles a general event and propagates it to registered listeners.
             *
             * This method processes a specific SFML event and ensures it is delivered
             * to all listeners registered with the event manager. It serves as a
             * centralized method for responding to general SFML events, maintaining
             * consistency in event dispatching. The method can be extended for custom
             * event handling logic.
             *
             * @param event A constant reference to the SFML event to be handled.
             *              This contains details about the event, such as type
             *              and associated data.
             */
        protected:
            virtual void general_event(const sf::Event &event);
            std::vector<IEventListener *> m_listeners;
        };
    } // event
} // bnjkit
#endif //I_EVENT_MANAGER_HPP
