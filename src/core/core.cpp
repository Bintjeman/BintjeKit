/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.cpp
 */
#include "bintjekit/core/core.hpp"
#include <iostream>
#include "bintjekit/window/i_main_window.hpp"
namespace bnjkit::core {
    Core::Core() {
        std::cout << "Constructor of Core" << std::endl;
    }
    Core::~Core() {
        std::cout << "Destructor of Core" << std::endl;
    }
    void Core::set_modules(std::unique_ptr<window::IMainWindow> window) {
        this->m_main_window = std::move(window);
    }
    void Core::run() {
        std::cout << "Running Core" << std::endl;
    }
} // bnjkit
