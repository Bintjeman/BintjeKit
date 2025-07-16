/*!
 * @author bintjeman
 * @date 01.07.25
 * @name eventmanager.cpp
 */

#include "event_manager.hpp"
#include <spdlog/spdlog.h>
#include <bintjekit/event_manager/event_helper.hpp>
#include <bintjekit/core/core.hpp>
#include "evobot_engine/evobot_engine.hpp"
#include "renderer/renderer.hpp"

namespace evo::event {
    void EventManager::initialise() {
    }
    void EventManager::configure() {
        ICoreEventHandler::configure();
        m_logger->info("evo::event::EventManager::configure");
        m_zoom_offset = m_settings.get_or_set("/Renderer/Camera/Zoom offset", 0.1f);
        m_zoom_offset_multiplier = m_settings.get_or_set(
            "/Renderer/Camera/Zoom offset multiplier", 2.f);
        m_camera_speed = m_settings.get_or_set("/Renderer/Camera/Speed", 10.f);
        m_camera_speed_multiplier = m_settings.get_or_set(
            "/Renderer/Camera/Speed multiplier", 2.f);
    }
    void EventManager::on_quit() {
        m_logger->info("evo::event::EventManager::on_quit");
        m_settings.set("/Renderer/Camera/Zoom offset", m_zoom_offset);
        m_settings.set(
            "/Renderer/Camera/Zoom offset multiplier", m_zoom_offset_multiplier);
        m_settings.set("/Renderer/Camera/Speed", m_camera_speed);
        m_settings.set(
            "/Renderer/Camera/Speed multiplier", m_camera_speed_multiplier);
    }
    void EventManager::on_sfml_event(const sf::Event& event) {
        auto& evo_renderer = dynamic_cast<renderer::Renderer&>(m_core->renderer());
        auto& evo_engine = dynamic_cast<engine::EvobotEngine&>(m_core->engine());
        if (const auto& key_pressed = event.getIf<sf::Event::KeyPressed>()) {
            m_logger->trace("key pressed: {}", static_cast<int>(key_pressed->code));
            const auto camera_speed = [_camera_speed = m_camera_speed,camera_speed_multiplier =
                        m_camera_speed_multiplier]() {
                if (bnjkit::event::shift()) {
                    return _camera_speed * camera_speed_multiplier;
                }
                return _camera_speed;
            };
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
#pragma clang diagnostic ignored "-Wswitch-enum"
            switch (key_pressed->code) {
                // Camera controls
                case sf::Keyboard::Key::A:
                    evo_renderer.camera_move({- camera_speed(), 0.f});
                    break;
                case sf::Keyboard::Key::D:
                    evo_renderer.camera_move({camera_speed(), 0.f});
                    break;
                case sf::Keyboard::Key::W:
                    evo_renderer.camera_move({0.f, - camera_speed()});
                    break;
                case sf::Keyboard::Key::S:
                    evo_renderer.camera_move({0.f, camera_speed()});
                    break;
                case sf::Keyboard::Key::C:
                    evo_renderer.resize_views();
                    break;
                // World controls
                case sf::Keyboard::Key::N:
                    evo_engine.new_world();
                    evo_renderer.resize_views();
                    stop();
                    break;
                case sf::Keyboard::Key::Space:
                    pause_button();
                    break;
                case sf::Keyboard::Key::Period:
                    evo_engine.update();
                    break;
                default:
                    break;
            }
#pragma clang diagnostic pop
        }
        if (const auto& mouse_scrolled = event.getIf<sf::Event::MouseWheelScrolled>()) {
            m_logger->trace("mouse scrolled: {}", mouse_scrolled->delta);
            const auto zoom_factor[[maybe_unused]] = [zoom_factor = m_zoom_offset,
                        zoom_ratio_multiplier
                        =
                        m_zoom_offset_multiplier]() {
                if (bnjkit::event::shift()) {
                    return zoom_factor * zoom_ratio_multiplier;
                }
                return zoom_factor;
            };
            if (mouse_scrolled->delta > 0) {
                m_logger->trace("zoom in: {}", zoom_factor());
                evo_renderer.camera_zoom(1 + zoom_factor());
            } else {
                m_logger->trace("zoom out: {}", zoom_factor());
                evo_renderer.camera_zoom(1 - zoom_factor());
            }
        }
    }
    std::string EventManager::name() const {
        return "evo::event::EventManager";
    }
    void EventManager::run_button() {
        auto engine_state = m_core->engine().state();
        if (engine_state != bnjkit::ecs::IEngine::State::EMPTY) {
            run();
        }
    }
    void EventManager::pause_button() {
        switch (m_core->state()) {
            case bnjkit::core::Core::State::RUNNING:
                pause();
                break;
            case bnjkit::core::Core::State::PAUSED:
            case bnjkit::core::Core::State::STOPPED:
                run();
                break;
        }
    }
    void EventManager::stop_button() {
        stop();
        auto& evobot_engine = dynamic_cast<engine::EvobotEngine&>(m_core->engine());
        evobot_engine.clear();
    }
    void EventManager::run() {
        m_core->set_state(bnjkit::core::Core::State::RUNNING);
    }
    void EventManager::pause() {
        m_core->set_state(bnjkit::core::Core::State::PAUSED);
    }
    void EventManager::stop() {
        m_core->set_state(bnjkit::core::Core::State::STOPPED);
    }
}
