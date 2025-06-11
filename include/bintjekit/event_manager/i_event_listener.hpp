/*!
 * @author bintjeman
 * @date 11.06.25
 * @name event_listener.hpp
 */

#ifndef I_EVENT_LISTENER_HPP
#define I_EVENT_LISTENER_HPP
#pragma once
namespace sf {
    class Event;
} // sf
namespace bnjkit {
    namespace event {
        class IEvent;

        class IEventListener {
        public:
            virtual ~IEventListener();
            virtual void on_sfml_event(const sf::Event &event) =0;
        };
    } // event
} // bnjkit

#endif // I_EVENT_LISTENER_HPP
