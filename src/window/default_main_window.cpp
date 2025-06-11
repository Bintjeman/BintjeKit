/*!
 * @author bintjeman
 * @date 11.06.25
 * @name default_main_window.cpp
 */

#include "bintjekit/window/default_main_window.hpp"
#include <iostream>
namespace bnjkit::window {
    DefaultMainWindow::DefaultMainWindow() {
        std::cout << "Constructor of DefaultMainWindow" << std::endl;
    }
    DefaultMainWindow::~DefaultMainWindow() {
        std::cout << "Destructor of DefaultMainWindow" << std::endl;
    }
    void DefaultMainWindow::initialise() {
        IMainWindow::initialise();
    }
    void DefaultMainWindow::configure() {
        IMainWindow::configure();
    }
    void DefaultMainWindow::show() {
        this->create(sf::VideoMode(sf::Vector2u(800, 600)), "BintjeKit", sf::Style::Default);
    }
} // bnjkit::window