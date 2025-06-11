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
    IMainWindow::~IMainWindow() {
        std::cout << "Destructor of MainWindow" << std::endl;
    }
    void IMainWindow::show() {
    }
}
