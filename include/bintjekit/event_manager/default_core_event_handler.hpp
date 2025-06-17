/*!
 * @author bintjeman
 * @date 16.06.25
 * @name DefaultCoreEventHandler.hpp
 */

#ifndef DEFAULTCOREEVENTHANDLER_HPP
#define DEFAULTCOREEVENTHANDLER_HPP
#pragma once
#include "bintjekit/event_manager/i_core_event_handler.hpp"
#include <SFML/Window/Event.hpp>
namespace bnjkit {
    namespace event {
        class DefaultCoreEventHandler : public ICoreEventHandler {
        public:
            void on_sfml_event(const sf::Event &event) override;
        }
        ;
    } // event
} // bnjkit
#endif //DEFAULTCOREEVENTHANDLER_HPP
