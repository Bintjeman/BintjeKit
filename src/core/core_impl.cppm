/*!
 * @file core_impl.cppm
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
export module core:impl;
import :interface;
import window;
namespace bik::core {
    Core::Core() {
        window_ = std::make_shared<window::Window>();
    }

    void Core::hw() {
        std::cout << "Je suis core de bintjeKit !" << std::endl;
        window_->hw();
    }
}
