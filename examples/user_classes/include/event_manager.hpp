/*!
 * @author bintjeman
 * @date 11.06.25
 * @name event_manager.hpp
 */

#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP
#pragma once
#include <bintjekit/event_manager/i_event_manager.hpp>

namespace usr {
    class EventManager : public bnjkit::event::IEventManager {
    public:
        ~EventManager() override;
        void initialise() override;
        void configure() override;
        void process_events(sf::Window &window) override;
    };
} // usr
#endif //EVENT_MANAGER_HPP
