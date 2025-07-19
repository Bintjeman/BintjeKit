/*!
 * @author bintjeman
 * @date 19.07.25
 * @name event_manager.cpp
 */

#include "event_manager.hpp"

#include "bintjekit/core/module_set.hpp"
#include "bintjekit/event_manager/event_helper.hpp"
#include "bintjekit/renderer/i_renderer.hpp"
#include "bintjekit/window/i_main_window.hpp"

namespace bil {
    void EventManager::configure() {
        m_logger->trace("Configuring EventManager");
        DefaultEventManager::configure();

    }
    void EventManager::process_events() {
        static auto& window = m_modules->window();
        static auto& renderer = m_modules->renderer();
        while (const auto& event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.request_close();
            }
            if (event->is<sf::Event::Resized>()) {
                m_logger->trace("Resized");
                renderer.resize_views();
            }
            if (const auto& key_pressed = event->getIf<sf::Event::KeyPressed>()) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
                switch (key_pressed->code) {
                    case sf::Keyboard::Key::Q:
                        if (bnjkit::event::ctrl()) {
                            window.request_close();
                        }
                        break;
                    case sf::Keyboard::Key::C:
                        if (bnjkit::event::ctrl()) {
                            renderer.resize_views();
                        }
                        break;
                    default: break;
                }
#pragma clang diagnostic pop
            }
        }
    }
    std::string EventManager::name() const {
        return DefaultEventManager::name();
    }
} // bil
