/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.cpp
 */
#include "bintjekit/core/core.hpp"
#include <iostream>
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/event_manager/i_event_manager.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/renderer/i_renderer.hpp"

namespace bnjkit::core {
    Core::Core() {
        std::cout << "Constructor of Core" << std::endl;
    }

    Core::~Core() {
        std::cout << "Destructor of Core" << std::endl;
    }

    void Core::set_modules(std::unique_ptr<window::IMainWindow> window,
                           std::unique_ptr<event::IEventManager> event_manager,
                           std::unique_ptr<engine::IEngine> engine,
                           std::unique_ptr<renderer::IRenderer> renderer,
                           std::unique_ptr<renderer::IEngineRenderer> engine_renderer) {
        this->m_main_window = std::move(window);
        this->m_event_manager = std::move(event_manager);
        this->m_engine = std::move(engine);
        this->m_renderer = std::move(renderer);
        this->m_engine_renderer = std::move(engine_renderer);
    }

    void Core::run() {
        std::cout << "Running Core" << std::endl;
        this->m_main_window->show();
        m_renderer->configure();
        while (this->m_main_window->isOpen()) {
            this->m_event_manager->process_events(*this->m_main_window);
            if (engine_pulser()) {
                this->m_engine->update();
            }
            if (renderer_pulser()) {
                this->m_renderer->render();
            }
        }
        std::cout << "Core finished" << std::endl;
    }
} // bnjkit
