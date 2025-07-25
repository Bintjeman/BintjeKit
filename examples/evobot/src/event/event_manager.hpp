/*!
 * @author bintjeman
 * @date 23.07.25
 * @name event_manager.hpp
 */
#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP
#pragma once
#include <bintjekit/event_manager/i_event_manager.hpp>

namespace evo::event {
    class EventManager final : public bnjkit::event::IEventManager {
    public:
        EventManager();
        ~EventManager() override;
        void configure() override;
        void process_events() override;
        [[nodiscard]] std::string name() const override;

    private:
        float camera_speed() const;
        float zoom_factor() const;
        void key_pressed(const sf::Event::KeyPressed& key_pressed) const;
        void close() const;

        bool m_camera_relative{true};
        float m_zoom_factor_multiplier{2.f};
        float m_zoom_factor{0.1f};
        float m_camera_speed_multiplier{2.f};
        float m_camera_speed{0.75f};
        float m_camera_speed_ratio_multiplier{2.f};
        float m_camera_speed_ratio{0.075f};
    };
}

#endif
