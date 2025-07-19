/*!
 * @author bintjeman
 * @date 19.07.25
 * @name event_manager.hpp
 */

#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP
#pragma once
#include <bintjekit/event_manager/default_event_manager.hpp>

namespace bil {
    class EventManager : public bnjkit::event::DefaultEventManager {
    public:
        EventManager();
        ~EventManager();
        void configure() override;
        void process_events() override;
        [[nodiscard]] std::string name() const override;
    private:
        bool m_camera_relative = false;
        float m_camera_speed = 0.01f;
        float m_camera_speed_multiplier = 2.0f;
        float m_camera_speed_ratio = 0.01f;
        float m_camera_speed_ratio_multiplier = 2.0f;
        float m_zoom_factor = 0.075f;
        float m_zoom_factor_multiplier = 2.0f;
    };
} // bil

#endif //EVENT_MANAGER_HPP
