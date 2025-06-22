/*!
 * @author bintjeman
 * @date 11.06.25
 * @name default_main_window.cpp
 */
#include "bintjekit/window/default_main_window.hpp"

#include <imgui-SFML.h>
#include "fmt_sfml/fmt_sfml.hpp"
#include "bintjekit/core/logger.hpp"

namespace bnjkit::window {
    DefaultMainWindow::DefaultMainWindow(): IMainWindow() {
        m_logger->warn("Constructor of DefaultMainWindow");
    }

    DefaultMainWindow::~DefaultMainWindow() {
        m_logger->warn("Destructor of DefaultMainWindow");
    }

    void DefaultMainWindow::initialise() {
        m_logger->warn("Initialising DefaultMainWindow");
        IMainWindow::initialise();
    }

    void DefaultMainWindow::configure() {
        m_logger->warn("Configuring DefaultMainWindow");
        IMainWindow::configure();
    }

    void DefaultMainWindow::show() {
        m_logger->warn("Showing DefaultMainWindow");
        IMainWindow::show();
        this->create(sf::VideoMode(getSize()), "", sf::Style::Default);
        m_logger->trace("Showing DefaultMainWindow: size: {}, title: {}", this->getSize(), title);
    }

    void DefaultMainWindow::on_sfml_event(const sf::Event &event) {
        IMainWindow::on_sfml_event(event);
        if (const auto *key_pressed = event.getIf<sf::Event::KeyPressed>()) {
            if (key_pressed->scancode == sf::Keyboard::Scancode::Q) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)) {
                    close();
                }
            }
        }
    }
} // bnjkit::window
