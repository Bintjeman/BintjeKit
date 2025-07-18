/*!
 * @author bintjeman
 * @date 18.07.25
 * @name default_event_manager.cpp
 *
 */
#include "bintjekit/event_manager/default_event_manager.hpp"
#include <spdlog/spdlog.h>

#include "bintjekit/core/module_set.hpp"
#include "bintjekit/window/i_main_window.hpp"

namespace bnjkit::event {
    DefaultEventManager::DefaultEventManager() {
        m_logger->warn("DefaultEventManager created");
    }
    DefaultEventManager::~DefaultEventManager() {
        m_logger->warn("DefaultEventManager destroyed");
    }
    void DefaultEventManager::process_events() {
        IEventManager::process_events();
        static auto& window = m_modules->window();
        while (const auto& event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
    }
}
