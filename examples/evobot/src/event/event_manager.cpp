/*!
 * @author bintjeman
 * @date 23.07.25
 * @name event_manager.cpp
 */
#include "event_manager.hpp"
#include <spdlog/spdlog.h>
#include <bintjekit/event_manager/event_helper.hpp>
#include <bintjekit/utils/d2/d2.hpp>
#include <bintjekit/core/module_set.hpp>
#include <bintjekit/imgui/i_imgui_renderer.hpp>
#include <bintjekit/renderer/i_renderer.hpp>
#include <bintjekit/window/i_main_window.hpp>
#include "imgui/imgui_renderer.hpp"
#include "engine/engine.hpp"

namespace evo::event {
    EventManager::EventManager() {
        m_logger->info("Build {}", name());
    }

    EventManager::~EventManager() {
        m_logger->info("Destroy {}", name());
    }
    void EventManager::configure() {
        m_logger->trace("Configure {}", name());
        m_camera_relative = m_settings.get_or_set("/Camera/Relative", m_camera_relative);
        m_zoom_factor_multiplier = m_settings.get_or_set("/Camera/Zoom multiplier", m_zoom_factor_multiplier);
        m_zoom_factor = m_settings.get_or_set("/Camera/Zoom factor", m_zoom_factor);
        m_camera_speed_multiplier = m_settings.get_or_set("/Camera/Speed multiplier", m_camera_speed_multiplier);
        m_camera_speed = m_settings.get_or_set("/Camera/Speed factor", m_camera_speed);
        m_camera_speed_ratio_multiplier = m_settings.get_or_set("/Camera/Speed ratio multiplier",
                                                                m_camera_speed_ratio_multiplier
        );
        m_camera_speed_ratio = m_settings.get_or_set("/Camera/Speed ratio factor", m_camera_speed_ratio);
    }

    void EventManager::process_events() {
        static auto& window = m_modules->window();
        static auto& imgui = m_modules->imgui_renderer();
        static auto& renderer = m_modules->renderer();
        while (const auto event = window.pollEvent()) {
            if (imgui::ImGuiRenderer::has_focus()) {
                imgui.process_events(event.value());
            } else {
                if (event->is<sf::Event::Closed>()) {
                    close();
                } else if (const auto key_event = event->getIf<sf::Event::KeyPressed>()) {
                    key_pressed(* key_event);
                } else if (const auto mouse_event = event->getIf<sf::Event::MouseWheelScrolled>()) {
                    if (mouse_event->delta > 0.f) {
                        renderer.engine_view().zoom(1 + zoom_factor());
                    } else if (mouse_event->delta < 0.f) {
                        renderer.engine_view().zoom(1 - zoom_factor());
                    }
                }
            }
        }
    }

    std::string EventManager::name() const {
        return "Evobot Event Manager";
    }

    float EventManager::camera_speed() const {
        static auto& renderer = m_modules->renderer();
        if (m_camera_relative) {
            const auto& view = renderer.engine_view();
            float speed = bnjkit::utils::d2::min_sf(view.getSize()) * m_camera_speed_ratio;
            speed = bnjkit::event::shift()
                        ? m_camera_speed_ratio_multiplier * speed
                        : speed;
            return speed;
        } else {
            return bnjkit::event::shift()
                       ? m_camera_speed_multiplier * m_camera_speed
                       : m_camera_speed;
        }
    }
    float EventManager::zoom_factor() const {
        return bnjkit::event::shift()
                   ? m_zoom_factor_multiplier * m_zoom_factor
                   : m_zoom_factor;
    }
    void EventManager::key_pressed(const sf::Event::KeyPressed& key_pressed) const {
        static auto& renderer = m_modules->renderer();
        static auto& engine = m_modules->engine();
        static auto& evobot_engine = dynamic_cast<engine::Engine&>(engine);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
        switch (key_pressed.code) {
            case sf::Keyboard::Key::Q: if (bnjkit::event::ctrl()) {
                    close();
                }
                break;
            case sf::Keyboard::Key::A: renderer.engine_view().
                        move(sf::Vector2f(- 1.f, 0.f) * camera_speed());
                break;
            case sf::Keyboard::Key::D: renderer.engine_view().move(sf::Vector2f(1.f, 0.f) * camera_speed());
                break;
            case sf::Keyboard::Key::W: renderer.engine_view().
                        move(sf::Vector2f(0.f, - 1.f) * camera_speed());
                break;
            case sf::Keyboard::Key::S: renderer.engine_view().move(sf::Vector2f(0.f, 1.f) * camera_speed());
                break;
            case sf::Keyboard::Key::C: if (bnjkit::event::ctrl()) {
                    renderer.resize_views();
                }
                break;
            case sf::Keyboard::Key::N: if (bnjkit::event::ctrl()) {
                    evobot_engine.new_world();
                    renderer.resize_views();
                }
                break;
            default: ;
        }
#pragma  clang diagnostic pop
    }

    void EventManager::close() const {
        m_logger->info("EventManager: Close request");
        m_modules->window().request_close();
    }
}
