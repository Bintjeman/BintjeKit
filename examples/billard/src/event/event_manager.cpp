/*!
 * @author bintjeman
 * @date 19.07.25
 * @name event_manager.cpp
 */

#include "event_manager.hpp"
#include <bintjekit/core/module_set.hpp>
#include <bintjekit/event_manager/event_helper.hpp>
#include <bintjekit/renderer/i_renderer.hpp>
#include <bintjekit/utils/d2/d2.hpp>
#include <bintjekit/utils/time/time.hpp>
#include <bintjekit/window/i_main_window.hpp>
#include "engine/billard.hpp"

namespace bil {
    EventManager::EventManager() {
        m_logger->info("Billard EventManager created");
    }
    EventManager::~EventManager() {
        m_logger->info("Billard EventManager destroyed");
    }
    void EventManager::configure() {
        m_logger->trace("Configuring Billard EventManager");
        DefaultEventManager::configure();
        m_camera_relative = m_settings.get_or_set("/Camera relative", false);
        m_camera_speed = m_settings.get_or_set("/Camera speed", 0.01f);
        m_camera_speed_multiplier = m_settings.get_or_set("/Camera speed multiplier", 2.0f);
        m_camera_speed_ratio = m_settings.get_or_set("/Camera speed ratio", 0.01f);
        m_camera_speed_ratio_multiplier = m_settings.get_or_set("/Camera speed ratio multiplier", 2.0f);
        m_zoom_factor = m_settings.get_or_set("/Zoom factor", 0.01f);
        m_zoom_factor_multiplier = m_settings.get_or_set("/Zoom factor multiplier", 2.0f);
    }
    void EventManager::process_events() {
        static auto& window = m_modules->window();
        static auto& renderer = m_modules->renderer();
        static auto& billard = dynamic_cast<Billard&>(m_modules->engine());
        while (const auto& event = window.pollEvent()) {
            auto camera_speed = [this]() {
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
            };
            auto zoom_factor = [this]() {
                return bnjkit::event::shift()
                           ? m_zoom_factor_multiplier * m_zoom_factor
                           : m_zoom_factor;
            };
            // Windows events
            if (event->is<sf::Event::Closed>()) {
                window.request_close();
            }
            if (event->is<sf::Event::Resized>()) {
                m_logger->trace("Resized");
                renderer.resize_views();
            }
            // Mouses events
            if (const auto mouse_clicked = event->getIf<sf::Event::MouseButtonPressed>()) {
                static bnjkit::utils::time::Clock clock;
                static bool first_click = true;
                if (mouse_clicked->button == sf::Mouse::Button::Left) {
                    if (first_click) {
                        clock.start();
                        first_click = false;
                    } else {
                        const auto elapsed = clock.get();
                        constexpr long int double_click_threshold = 500000;
                        if (elapsed <= double_click_threshold) {
                            m_logger->trace("Double click");
                            billard.add_ball();
                            first_click = true;
                        } else {
                            clock.start();
                        }
                    }
                }
            }
            if (const auto mouse_srolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
                float ratio = zoom_factor();
                m_logger->trace("Mouse wheel scrolled: {}", mouse_srolled->delta);
                m_logger->trace("Zoom factor: {}", ratio);
                if (mouse_srolled->delta > 0) {
                    renderer.engine_view().zoom(1 - ratio);
                } else if (mouse_srolled->delta < 0) {
                    renderer.engine_view().zoom(1 + ratio);
                }
            }
            if (const auto& key_pressed = event->getIf<sf::Event::KeyPressed>()) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
                switch (key_pressed->code) {
                    // Application controls
                    case sf::Keyboard::Key::Q:
                        if (bnjkit::event::ctrl()) {
                            window.request_close();
                        }
                        break;
                    // View & renderer
                    case sf::Keyboard::Key::C:
                        if (bnjkit::event::ctrl()) {
                            renderer.resize_views();
                        }
                        break;
                    case sf::Keyboard::Key::A:
                        renderer.engine_view().move(sf::Vector2f{- camera_speed(), 0.f});
                        break;
                    case sf::Keyboard::Key::D:
                        renderer.engine_view().move(sf::Vector2f{camera_speed(), 0.f});
                        break;
                    case sf::Keyboard::Key::W:
                        renderer.engine_view().move(sf::Vector2f{0.f, - camera_speed()});
                        break;
                    case sf::Keyboard::Key::S:
                        renderer.engine_view().move(sf::Vector2f{0.f, camera_speed()});
                        break;
                    default: break;
                }
#pragma clang diagnostic pop
            }
        }
    }

    std::string EventManager::name() const {
        return "Billard EventManager";
    }
} // bil
