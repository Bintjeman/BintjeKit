/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include <iostream>

namespace bnjkit::window {
    IMainWindow::IMainWindow() {
        std::cout << "Constructor of MainWindow" << std::endl;
    }

    IMainWindow::~IMainWindow() noexcept {
        std::cout << "Destructor of MainWindow" << std::endl;
    }

    void IMainWindow::show() {
    }

    void IMainWindow::on_sfml_event(const sf::Event &event) {
        if (event.is<sf::Event::Closed>()) {
            close();
        }
        if (const auto *key_pressed = event.getIf<sf::Event::KeyPressed>()) {
            if (key_pressed->scancode == sf::Keyboard::Scancode::Q) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)) {
                    close();
                }
            }
        }
    }
}
