/*!
 * @file window_impl.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <iostream>
export module window:impl;
import :interface;
import logger;
namespace bik::window {
    Window::Window() {
        logger::getLogger()->info("Window::Window()");
    }

    Window::~Window() {
        logger::getLogger()->info("Window::~Window()");
    }

    void Window::hw() {
        std::cout << "Je suis window de bintjeKit !" << std::endl;
    }
}
