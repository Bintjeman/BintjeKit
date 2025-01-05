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
import factory;
namespace bik::core {
    Core::Core() {
        factory_ = std::make_unique<factory::Factory>();
    }

    Core::Core(std::unique_ptr<factory::Factory> factory) {
        factory_ = std::move(factory);
        window_ = factory_->create_window();
    }

    Core::~Core() {
    }

    void Core::hw() {
        std::cout << "Je suis core de bintjeKit !" << std::endl;
        window_->hw();
    }
}
