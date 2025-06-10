/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/main_window.hpp"
#include <iostream>
namespace bnjkit {

    MainWindow::MainWindow() {
        std::cout << "Constructor of MainWindow" << std::endl;
    }
    MainWindow::~MainWindow() {
        std::cout << "Destructor of MainWindow" << std::endl;
    }
    void MainWindow::open() {
        this->create(sf::VideoMode(sf::Vector2u(800, 600)), "BintjeKit", sf::Style::Default);
    }
}
