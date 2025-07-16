/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.cpp
 */
#include "bintjekit/core/core_builder.hpp"
#include "bintjekit/core/core.hpp"
// Utils
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"
// Interface modules
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/event_manager/event_manager.hpp"
#include "bintjekit/renderer/i_renderer.hpp"
#include "bintjekit/renderer/i_engine_renderer.hpp"
#include "bintjekit/event_manager/i_core_event_handler.hpp"
// defaults modules

namespace bnjkit::core {
    CoreBuilder::CoreBuilder() {
        m_logger = Logger::get_logger(module_names::CORE);
        m_logger->info("Constructor of CoreBuilder");
    }

    CoreBuilder::~CoreBuilder() {
        m_logger->info("Destructor of CoreBuilder");
    }

    CoreBuilder& CoreBuilder::set_window_module(std::unique_ptr<window::IMainWindow> window) {
        m_logger->trace("Setting window module");
        m_window = std::move(window);
        return *this;
    }

    CoreBuilder& CoreBuilder::set_event_manager_module(std::unique_ptr<event::EventManager> event_manager) {
        m_logger->trace("Setting event manager module");
        m_event_manager = std::move(event_manager);
        return *this;
    }

    CoreBuilder& CoreBuilder::set_engine_module(std::unique_ptr<ecs::IEngine> engine) {
        m_logger->trace("Setting engine module");
        m_engine = std::move(engine);
        return *this;
    }

    CoreBuilder& CoreBuilder::set_renderer_module(std::unique_ptr<renderer::IRenderer> renderer) {
        m_logger->trace("Setting renderer module");
        m_renderer = std::move(renderer);
        return *this;
    }

    CoreBuilder& CoreBuilder::set_engine_renderer(std::unique_ptr<renderer::IEngineRenderer> engine_renderer) {
        m_logger->trace("Setting engine renderer module");
        m_engine_renderer = std::move(engine_renderer);
        return *this;
    }

    CoreBuilder& CoreBuilder::set_imgui_renderer(std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer) {
        m_logger->trace("Setting imgui renderer module");
        m_imgui_renderer = std::move(imgui_renderer);
        return *this;
    }

    CoreBuilder& CoreBuilder::set_core_event_handler(std::unique_ptr<event::ICoreEventHandler> core_event_handler) {
        m_logger->trace("Setting core event handler");
        m_event_manager->set_core_event_handler(std::move(core_event_handler));
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
            m_event_manager = std::make_unique<event::EventManager>();
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
            m_engine = std::make_unique<ecs::IEngine>();
        }
        if (!m_engine_renderer) {
            m_logger->warn("No engine renderer module set. Using interface engine renderer module");
            m_engine_renderer.reset();
            m_engine_renderer = std::make_unique<renderer::IEngineRenderer>();
        }
        if (!m_core_event_handler) {
            m_logger->warn("No core event handler set. Using interface core event handler module");
            m_core_event_handler.reset();
            m_core_event_handler = std::make_unique<event::DefaultCoreEventHandler>();
        }
        if (m_event_manager) {
            m_core_event_handler->set_core(core.get());
            m_event_manager->set_core_event_handler(std::move(m_core_event_handler));
            m_event_manager->register_listener(m_window.get());
            m_event_manager->register_listener(m_renderer.get());
            m_event_manager->set_imgui_renderer(m_imgui_renderer.get());
            m_event_manager->register_listener(m_engine.get());
        }
        if (m_renderer) {
            m_renderer->set_engine(m_engine.get());
            m_renderer->set_render_window(m_window.get());
            m_renderer->set_engine_renderer(m_engine_renderer.get());
            m_renderer->set_core(core.get());
            m_renderer->set_imgui_renderer(m_imgui_renderer.get());
        }
        if (m_engine_renderer) {
            m_engine_renderer->set_engine(m_engine.get());
        }
        if (m_imgui_renderer) {
            m_imgui_renderer->set_window(m_window.get());
            m_imgui_renderer->set_engine(m_engine.get());
            m_imgui_renderer->set_core(core.get());
            m_imgui_renderer->set_renderer(m_renderer.get());
            m_imgui_renderer->set_core_event_handler(m_event_manager->get_core_event_handler());
        }
        m_engine->initialise();
        m_renderer->initialise();
        m_engine_renderer->initialise();
        // m_event_manager->initialise();
        m_window->initialise();
        core->set_modules(
            std::move(m_window),
            std::move(m_event_manager),
            std::move(m_engine),
            std::move(m_renderer),
            std::move(m_engine_renderer),
            std::move(m_imgui_renderer)
        );
        return core;
    }
} // bnjkit::core
