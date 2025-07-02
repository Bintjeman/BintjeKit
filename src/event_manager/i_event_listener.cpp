/*!
 * @author bintjeman
 * @date 11.06.25
 * @name event_listener.cpp
 */
#include "bintjekit/event_manager/i_event_listener.hpp"
namespace bnjkit {
    namespace event {
        IEventListener::~IEventListener() = default;

        void IEventListener::on_sfml_event(const sf::Event& event[[maybe_unused]]) {
        }
    } // event
} // bnjkit
