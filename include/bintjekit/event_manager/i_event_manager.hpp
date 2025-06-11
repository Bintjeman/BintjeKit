/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.hpp
 */
#ifndef I_EVENT_MANAGER_HPP
#define I_EVENT_MANAGER_HPP
#pragma once
#include "bintjekit/core/i_module.hpp"

namespace bnjkit {
    namespace event {
        class IEventManager : public core::IModule {
        public:
            IEventManager();
            ~IEventManager() override;
            void initialise() override;
            void configure() override;
        };
    } // event
} // bnjkit
#endif //I_EVENT_MANAGER_HPP
