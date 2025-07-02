/*!
 * @author bintjeman
 * @date 16.06.25
 * @name DefaultCoreEventHandler.hpp
 */

#ifndef BNJKIT_EVENT_DEFAULTCOREEVENTHANDLER_HPP
#define BNJKIT_EVENT_DEFAULTCOREEVENTHANDLER_HPP
#pragma once
#include <SFML/Window/Event.hpp>
#include "bintjekit/event_manager/i_core_event_handler.hpp"
namespace bnjkit {
    namespace event {
        class DefaultCoreEventHandler : public ICoreEventHandler {
        public:
            void on_sfml_event(const sf::Event& event) override;
            [[nodiscard]] std::string name() const override;
        };
    } // event
} // bnjkit
#endif // BNJKIT_EVENT_DEFAULTCOREEVENTHANDLER_HPP
