/*!
 * @file window_child.cpp
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
module window_child;
namespace min {
    WindowChild::~WindowChild() {
    }
    void WindowChild::hw() {
        Window::hw();
        std::cout << "Je suis window child de bintjeKit !" << std::endl;
    }
}
