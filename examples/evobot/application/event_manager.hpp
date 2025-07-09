/*!
 * @author bintjeman
 * @date 01.07.25
 * @name eventmanager.hpp
 */

#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
#pragma once
#include <bintjekit/event_manager/i_core_event_handler.hpp>

namespace evo {
    namespace renderer {
        class Renderer;
    } // renderer
    namespace event {
        class EventManager : public bnjkit::event::ICoreEventHandler {
        public:
            void initialise() override;
            void configure() override;
            void on_quit() override;
            void on_sfml_event(const sf::Event& event) override;
            [[nodiscard]] std::string name() const override;
            void run_button();
            void pause_button();
            void stop_button();
        private:
            void run();
            void pause();
            void stop();
            float m_zoom_offset{1.f};
            float m_zoom_offset_multiplier{1.f};
            float m_camera_speed{1.f};
            float m_camera_speed_multiplier{1.f};
        };
    } // event
} // evo

#endif //EVENTMANAGER_HPP
