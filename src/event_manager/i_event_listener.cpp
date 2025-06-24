/*!
 * @author bintjeman
 * @date 11.06.25
 * @name event_listener.cpp
 */

#include "bintjekit/event_manager/i_event_listener.hpp"
#include <SFML/Window/Keyboard.hpp>
namespace bnjkit {
    namespace event {
        IEventListener::~IEventListener() = default;
        bool IEventListener::shift() {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
        }
        bool IEventListener::ctrl() {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
        }
        bool IEventListener::alt() {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt);
        }
    } // event
} // bnjkit
