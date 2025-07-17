/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.hpp
 */
#ifndef BNJKIT_EVENT_I_EVENT_MANAGER_HPP
#define BNJKIT_EVENT_I_EVENT_MANAGER_HPP
#pragma once
#include <SFML/Window/Event.hpp>
#include "bintjekit/core/i_module.hpp"
namespace bnjkit::event {
    class IEventManager : public core::IModule {
        public:
        IEventManager();
        ~IEventManager() override;
        void initialise() override;
        void configure() override;
        void on_quit() override;
        void process_events(const sf::Event& event);
        [[nodiscard]] std::string name() const override;
        private:

    };
}
#endif // BNJKIT_EVENT_I_EVENT_MANAGER_HPP
