/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.cpp
 */

#include "bintjekit/event_manager/event_manager.hpp"
#include <algorithm>
#include <SFML/Window/Window.hpp>
#include <imgui-SFML.h>
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"
#include "bintjekit/event_manager/i_core_event_handler.hpp"
#include "bintjekit/renderer/i_bnjkit_imgui.hpp"

namespace bnjkit::event {
    EventManager::EventManager(): m_imgui_renderer(nullptr) {
        m_logger = core::Logger::get_logger(literals::logger::EVENT);
        m_logger->info("Constructor of IEventManager");
    }

    EventManager::~EventManager() {
        m_logger->info("Destructor of IEventManager");
    }
    void EventManager::configure() {
        m_logger->trace("Configuring event manager");
        m_core_event_handler->configure();
    }
    ICoreEventHandler* EventManager::get_core_event_handler() const {
        return m_core_event_handler.get();
    }
    void EventManager::set_imgui_renderer(renderer::IImGuiRenderer* renderer) {
        m_logger->trace("Setting imgui renderer");
        m_imgui_renderer = renderer;
    }
    void EventManager::set_core_event_handler(
        std::shared_ptr<ICoreEventHandler> core_event_handler) {
        m_logger->trace("Setting core event handler");
        m_core_event_handler = std::move(core_event_handler);
    }
    void EventManager::set_core_event_handler_settings(const conf::Node& settings) {
        m_logger->trace("Setting core event handler settings");
        m_core_event_handler->set_settings(settings);
    }
    void EventManager::set_core_event_handler_custom_settings(const conf::Node& settings) {
        m_logger->trace("Setting core event handler custom settings");
        m_core_event_handler->set_custom(settings);
    }
    void EventManager::register_listener(IEventListener* listener) {
        m_logger->trace("Registering listener");
        if (listener) {
            if (std::ranges::find(m_listeners, listener) == m_listeners.
                end()) {
                m_listeners.push_back(listener);
            }
        }
    }
    void EventManager::unregister_listener(IEventListener* listener) {
        m_logger->trace("Unregistering listener");
        const auto it = std::ranges::remove(m_listeners, listener).begin();
        m_listeners.erase(it, m_listeners.end());
    }
    void EventManager::process_events(sf::Window& window) {
        while (auto event = window.pollEvent()) {
            m_imgui_renderer->process_events(* event);
            for (auto* listener: m_listeners) {
                listener->on_sfml_event(* event);
            }
            m_logger->trace("Processing events");
            m_core_event_handler->on_sfml_event(* event);
            general_event(* event);
        }
    }
    void EventManager::on_quit() {
        m_logger->trace("Quitting event manager");
        m_core_event_handler->on_quit();
    }
    void EventManager::general_event(const sf::Event& event[[maybe_unused]]) const {
        m_logger->trace("General event");
    }
}
