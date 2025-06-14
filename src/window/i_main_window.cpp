/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"

namespace bnjkit::window {
    IMainWindow::IMainWindow() {
        m_logger = core::Logger::get_logger(core::module_names::WINDOW);
        m_logger->info("Constructor of IMainWindow");
    }

    IMainWindow::~IMainWindow() noexcept {
        m_logger->info("Destructor of IMainWindow");
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
