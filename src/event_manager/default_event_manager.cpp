/*!
 * @author bintjeman
 * @date 18.07.25
 * @name default_event_manager.cpp
 *
 */
#include "bintjekit/event_manager/default_event_manager.hpp"
#include <spdlog/spdlog.h>

#include "bintjekit/core/module_set.hpp"
#include "bintjekit/event_manager/event_helper.hpp"
#include "bintjekit/renderer/i_imgui_renderer.hpp"
#include "bintjekit/renderer/i_renderer.hpp"
#include "bintjekit/window/i_main_window.hpp"

namespace bnjkit::event {
    DefaultEventManager::DefaultEventManager() {
        m_logger->warn("DefaultEventManager created");
    }
    DefaultEventManager::~DefaultEventManager() {
        m_logger->warn("DefaultEventManager destroyed");
    }
    void DefaultEventManager::configure() {
        m_logger->warn("Configuring DefaultEventManager");
        IEventManager::configure();
    }
    void DefaultEventManager::process_events() {
        static auto& window = m_modules->window();
        static auto& renderer = m_modules->renderer();
        static auto& imgui_renderer = m_modules->imgui_renderer();
        while (const auto& event = window.pollEvent()) {
            imgui_renderer.process_events(*event);
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
                        if (ctrl()) {
                            window.request_close();
                        }
                        break;
                    case sf::Keyboard::Key::C:
                        if (ctrl()) {
                            renderer.resize_views();
                        }
                        break;
                    default: break;
                }
#pragma clang diagnostic pop
            }
        }
    }
    std::string DefaultEventManager::name() const {
        return "DefaultEventManager";
    }
}
