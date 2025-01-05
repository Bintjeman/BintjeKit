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
namespace bik::window {
    Window::Window() {
    }

    Window::~Window() {
    }

    void Window::hw() {
        std::cout << "Je suis window de bintjeKit !" << std::endl;
    }
}
