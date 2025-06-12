/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.cpp
 */
#include "bintjekit/core/core_builder.hpp"
#include "bintjekit/core/core.hpp"
// Interface modules
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/event_manager/i_event_manager.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/renderer/i_renderer.hpp"
// defaults modules
#include "bintjekit/window/default_main_window.hpp"
#include "bintjekit/event_manager/default_event_manager.hpp"

namespace bnjkit::core {
    CoreBuilder::CoreBuilder() {
    }

    CoreBuilder::~CoreBuilder() {
    }

    CoreBuilder &CoreBuilder::set_window_module(std::unique_ptr<window::IMainWindow> window) {
        m_window = std::move(window);
        return *this;
    }

    CoreBuilder &CoreBuilder::set_event_manager_module(std::unique_ptr<event::IEventManager> event_manager) {
        m_event_manager = std::move(event_manager);
        return *this;
    }

    std::unique_ptr<Core> CoreBuilder::build() {
        auto core = std::make_unique<Core>();
        if (!m_window) {
            m_window.reset();
            m_window = std::make_unique<window::DefaultMainWindow>();
        }
        if (!m_event_manager) {
            m_event_manager.reset();
            m_event_manager = std::make_unique<event::DefaultEventManager>();
        }
        m_event_manager->register_listener(m_window.get());
        core->set_modules(
            std::move(m_window),
            std::move(m_event_manager),
            std::move(m_engine),
            std::move(m_renderer));
        return core;
    }
} // bnjkit::core
