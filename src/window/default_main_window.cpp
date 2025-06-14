/*!
 * @author bintjeman
 * @date 11.06.25
 * @name default_main_window.cpp
 */
#include "bintjekit/window/default_main_window.hpp"
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
        const char *title = "BintjeKit";
        this->create(sf::VideoMode(sf::Vector2u(800, 600)), title, sf::Style::Default);
        m_logger->trace("Showing DefaultMainWindow: size: {}, title: {}", this->getSize(), title);
    }

    void DefaultMainWindow::on_sfml_event(const sf::Event &event) {
        if (event.is<sf::Event::Closed>()) {
            close();
        }
    }
} // bnjkit::window
