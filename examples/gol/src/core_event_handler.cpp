/*!
 * @author bintjeman
 * @date 17.06.25
 * @name core_event_handler.cpp
 */
#include "core_event_handler.hpp"
#include <SFML/Window/Event.hpp>
#include <spdlog/logger.h>
#include <bintjekit/core/core.hpp>

namespace gol {
    CoreEventHandler::CoreEventHandler() {
        m_logger->info("Constructor of CoreEventHandler");
    }

    CoreEventHandler::~CoreEventHandler() = default;

    void CoreEventHandler::on_sfml_event(const sf::Event& event) {
        m_logger->debug("CoreEventHandler: on_sfml_event");
        if (const auto keypressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keypressed->code == sf::Keyboard::Key::Space) {
                pause_button();
            }
        }
    }

    void CoreEventHandler::pause_button() {
        switch (m_core->state()) {
            case bnjkit::core::Core::State::RUNNING:
                m_core->set_state(bnjkit::core::Core::State::PAUSED);
                break;
            case bnjkit::core::Core::State::PAUSED:
            case bnjkit::core::Core::State::STOPPED:
                m_core->set_state(bnjkit::core::Core::State::RUNNING);
                break;
        }
    }
    std::string CoreEventHandler::name() const {
        return "CoreEventHandler";
    }
} // gol
