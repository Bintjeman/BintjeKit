/*!
 * @author bintjeman
 * @date 11.06.25
 * @name main_window.cpp
 */
#include "main_window.hpp"

namespace usr {
    MainWindow::MainWindow() = default;

    MainWindow::~MainWindow() = default;

    void MainWindow::show() {
        IMainWindow::show();
        this->create(sf::VideoMode(sf::Vector2u(800, 600)), "BintjeKit", sf::Style::Default);
    }

    void MainWindow::initialise() {
        IMainWindow::initialise();
    }

    void MainWindow::configure() {
        IMainWindow::configure();
    }

    void MainWindow::on_sfml_event(const sf::Event& event) {
        IMainWindow::on_sfml_event(event);
    }
    std::string MainWindow::name() const {
        return "MainWindow";
    }
} // usr
