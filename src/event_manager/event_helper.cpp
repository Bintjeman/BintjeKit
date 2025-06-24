/*!
 * @author bintjeman
 * @date 24.06.25
 * @name event_helper.cpp
 */
#include <SFML/Window/Keyboard.hpp>

namespace bnjkit {
    namespace event {
        bool shift() {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
        }
        bool ctrl() {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
        }
        bool alt() {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt);
        }
    }
} // bnjkit
