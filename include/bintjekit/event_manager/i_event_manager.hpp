/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.hpp
 */
#ifndef I_EVENT_MANAGER_HPP
#define I_EVENT_MANAGER_HPP
#pragma once
#include <vector>
#include "bintjekit/core/i_module.hpp"

namespace sf {
    class Window;
}

namespace bnjkit {
    namespace event {
        class IEventListener;
        // class IEvent;

        class IEventManager : public core::IModule {
        public:
            IEventManager();
            ~IEventManager() override;
            void initialise() override;
            void configure() override;
            virtual void register_listener(IEventListener *listener) =0;
            virtual void unregister_listener(IEventListener *listener) =0;
            virtual void process_events(sf::Window &window) =0;

        protected:
            std::vector<IEventListener *> m_listeners;
        };
    } // event
} // bnjkit
#endif //I_EVENT_MANAGER_HPP
