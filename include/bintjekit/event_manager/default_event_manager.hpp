/*!
 * @author bintjeman
 * @date 18.07.25
 * @name default_event_manager.hpp
 */

#ifndef BINTJEKIT_DEFAULT_EVENT_MANAGER_HPP
#define BINTJEKIT_DEFAULT_EVENT_MANAGER_HPP
#pragma once
#include "bintjekit/event_manager/i_event_manager.hpp"

namespace bnjkit::event {
    class DefaultEventManager : public IEventManager {
    public:
        DefaultEventManager();
        ~DefaultEventManager() override;
        void process_events() override;
        [[nodiscard]] std::string name() const override;
    };
}

#endif //BINTJEKIT_DEFAULT_EVENT_MANAGER_HPP
