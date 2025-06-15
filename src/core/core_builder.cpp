/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.cpp
 */
#include "bintjekit/core/core_builder.hpp"
#include "bintjekit/core/core.hpp"
// Utils
#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"
// Interface modules
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/event_manager/i_event_manager.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/renderer/i_renderer.hpp"
#include "bintjekit/renderer/i_engine_renderer.hpp"
// defaults modules
#include "bintjekit/window/default_main_window.hpp"
#include "bintjekit/event_manager/default_event_manager.hpp"
#include "bintjekit/renderer/default_renderer.hpp"

namespace bnjkit::core {
    CoreBuilder::CoreBuilder() {
        static bool initialized = false;
        if (!initialized) {
            Logger::initialize();
            initialized = true;
        }
        m_logger = Logger::get_logger(module_names::CORE);
        m_logger->info("Constructor of CoreBuilder");
    }

    CoreBuilder::~CoreBuilder() {
        m_logger->info("Destructor of CoreBuilder");
    }

    CoreBuilder &CoreBuilder::set_window_module(std::unique_ptr<window::IMainWindow> window) {
        m_logger->info("Setting window module");
        m_window = std::move(window);
        return *this;
    }

    CoreBuilder &CoreBuilder::set_event_manager_module(std::unique_ptr<event::IEventManager> event_manager) {
        m_logger->info("Setting event manager module");
        m_event_manager = std::move(event_manager);
        return *this;
    }

    CoreBuilder &CoreBuilder::set_engine_module(std::unique_ptr<engine::IEngine> engine) {
        m_logger->info("Setting engine module");
        m_engine = std::move(engine);
        return *this;
    }

    CoreBuilder &CoreBuilder::set_renderer_module(std::unique_ptr<renderer::IRenderer> renderer) {
        m_logger->info("Setting renderer module");
        m_renderer = std::move(renderer);
        return *this;
    }

    CoreBuilder &CoreBuilder::set_engine_renderer(std::unique_ptr<renderer::IEngineRenderer> engine_renderer) {
        m_logger->info("Setting engine renderer module");
        m_engine_renderer = std::move(engine_renderer);
        return *this;
    }

    CoreBuilder &CoreBuilder::set_imgui_renderer(std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer) {
        m_logger->info("Setting imgui renderer module");
        m_imgui_renderer = std::move(imgui_renderer);
        return *this;
    }

    std::unique_ptr<Core> CoreBuilder::build() {
        m_logger->info("Building Core");
        auto core = std::make_unique<Core>();
        if (!m_window) {
            m_logger->warn("No window module set. Using default window module");
            m_window.reset();
            m_window = std::make_unique<window::DefaultMainWindow>();
        }
        if (!m_event_manager) {
            m_logger->warn("No event manager module set. Using default event manager module");
            m_event_manager.reset();
            m_event_manager = std::make_unique<event::DefaultEventManager>();
        }
        if (!m_renderer) {
            m_logger->warn("No renderer module set. Using default renderer module");
            m_renderer.reset();
            m_renderer = std::make_unique<renderer::DefaultRenderer>();
        }
        if (!m_imgui_renderer) {
            m_logger->warn("No imgui renderer module set. Using interface imgui renderer module");
            m_imgui_renderer.reset();
            m_imgui_renderer = std::make_unique<renderer::IImGuiRenderer>();
        }
        if (!m_engine) {
            m_logger->warn("No engine module set. Using interface engine module");
            m_engine.reset();
            m_engine = std::make_unique<engine::IEngine>();
        }
        if (!m_engine_renderer) {
            m_logger->warn("No engine renderer module set. Using interface engine renderer module");
            m_engine_renderer.reset();
            m_engine_renderer = std::make_unique<renderer::IEngineRenderer>();
        }
        if (m_event_manager) {
            m_event_manager->register_listener(m_window.get());
            m_event_manager->register_listener(m_renderer.get());
            m_event_manager->set_imgui_renderer(m_imgui_renderer.get());
        }
        if (m_renderer) {
            m_renderer->set_engine(m_engine.get());
            m_renderer->set_render_window(m_window.get());
            m_renderer->set_engine_renderer(m_engine_renderer.get());
            m_renderer->set_imgui_renderer(m_imgui_renderer.get());
        }
        if (m_engine_renderer) {
            m_engine_renderer->set_engine(m_engine.get());
        }
        if (m_imgui_renderer) {
            m_imgui_renderer->set_window(m_window.get());
        }
        core->set_modules(
            std::move(m_window),
            std::move(m_event_manager),
            std::move(m_engine),
            std::move(m_renderer),
            std::move(m_engine_renderer),
            std::move(m_imgui_renderer));
        return core;
    }
} // bnjkit::core
