/*!
 * @author bintjeman
 * @date 16.06.25
 * @name ICoreEventHandler.hpp
 */
#ifndef ICOREEVENTHANDLER_HPP
#define ICOREEVENTHANDLER_HPP
#pragma once
#include <memory>
#include <spdlog/fwd.h>

#include "SFML/Window/Event.hpp"

namespace bnjkit {
    namespace core {
        class Core;
    }

    namespace event {
        class ICoreEventHandler {
        public:
            ICoreEventHandler();
            virtual ~ICoreEventHandler();
            virtual void set_core(core::Core *core);
            virtual void on_sfml_event(const sf::Event &event) =0;

        protected:
            core::Core *m_core;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // event
} // bnjkit
#endif //ICOREEVENTHANDLER_HPP
