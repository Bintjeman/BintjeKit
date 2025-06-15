/*!
 * @author bintjeman
 * @date 11.06.25
 * @name event_listener.hpp
 */

#ifndef I_EVENT_LISTENER_HPP
#define I_EVENT_LISTENER_HPP
#pragma once
#include <memory>
#include <spdlog/fwd.h>

namespace sf {
    class Event;
} // sf
namespace bnjkit {
    namespace event {
        class IEvent;

        /**
         * @class IEventListener
         * @brief Interface for event listeners.
         *
         * Provides an interface for objects that need to handle SFML events.
         * Implementing classes must define behavior for handling events by overriding the on_sfml_event method.
         */
        class IEventListener {
        public:
            virtual ~IEventListener();
            /**
             * @brief Handles SFML events.
             *
             * This method must be implemented by any class inheriting from IEventListener.
             * It defines the behavior for processing and responding to a specific SFML event.
             *
             * @param event The SFML event that needs to be handled.
             */
            virtual void on_sfml_event(const sf::Event &event) = 0;

        protected:
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // event
} // bnjkit

#endif // I_EVENT_LISTENER_HPP
