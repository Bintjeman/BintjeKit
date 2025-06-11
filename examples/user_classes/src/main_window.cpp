/*!
 * @author bintjeman
 * @date 11.06.25
 * @name main_window.cpp
 */
#include "main_window.hpp"

namespace usr {
    MainWindow::MainWindow() : IMainWindow() {
    }

    MainWindow::~MainWindow(){}

    void MainWindow::show() {
    }

    void MainWindow::initialise() {
        IMainWindow::initialise();
    }

    void MainWindow::configure() {
        IMainWindow::configure();
    }

    void MainWindow::on_sfml_event(const sf::Event &event) {
    }
} // usr
