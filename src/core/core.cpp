/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.cpp
 */
#include "bintjekit/core/core.hpp"
#include <iostream>
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/event_manager/i_event_manager.hpp"

namespace bnjkit::core {
    Core::Core() {
        std::cout << "Constructor of Core" << std::endl;
    }

    Core::~Core() {
        std::cout << "Destructor of Core" << std::endl;
    }

    void Core::set_modules(std::unique_ptr<window::IMainWindow> window,
                           std::unique_ptr<event::IEventManager> event_manager) {
        this->m_main_window = std::move(window);
        this->m_event_manager = std::move(event_manager);
    }

    void Core::run() {
        std::cout << "Running Core" << std::endl;
        this->m_main_window->show();
        while (const auto &event = this->m_main_window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_main_window->close();
            }
        }
        std::cout << "Core finished" << std::endl;
    }
} // bnjkit
