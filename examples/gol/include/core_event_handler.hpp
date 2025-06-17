/*!
 * @author bintjeman
 * @date 17.06.25
 * @name core_event_handler.hpp
 */

#ifndef CORE_EVENT_HANDLER_HPP
#define CORE_EVENT_HANDLER_HPP
#pragma once
#include <bintjekit/event_manager/i_core_event_handler.hpp>

namespace gol {
    class CoreEventHandler : public bnjkit::event::ICoreEventHandler {
    public:
        CoreEventHandler();
        ~CoreEventHandler() override;
        void on_sfml_event(const sf::Event &event) override;

        private:
        void pause_button();
    };
} // gol

#endif //CORE_EVENT_HANDLER_HPP
