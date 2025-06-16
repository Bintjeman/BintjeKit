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
        class IEventListener {
        public:
            virtual ~IEventListener();
            virtual void on_sfml_event(const sf::Event &event) = 0;
        protected:
            std::shared_ptr<spdlog::logger> m_listener_logger;
        };
    } // event
} // bnjkit

#endif // I_EVENT_LISTENER_HPP
