/*!
 * @file factory_child.cpp
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
module factory_child;
import window;
import window_child;
import factory;
namespace min {
    Child::~Child() {
    }
    std::shared_ptr<bik::window::Window> Child::create_window() {
        return std::make_shared<min::WindowChild>();
    }
}