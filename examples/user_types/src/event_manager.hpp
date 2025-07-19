/*!
 * @author bintjeman
 * @date 18.07.25
 * @name event_manager.hpp
 */

#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP
#pragma once
#include <bintjekit/event_manager/default_event_manager.hpp>
namespace utypes {

class EventManager :public bnjkit::event::DefaultEventManager{
public:
    EventManager();
    ~EventManager();
};

} // utypes

#endif //EVENT_MANAGER_HPP
