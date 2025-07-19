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
        void configure() override;
        void process_events() override;
        [[nodiscard]] std::string name() const override;
    };
} // bil

#endif //EVENT_MANAGER_HPP
