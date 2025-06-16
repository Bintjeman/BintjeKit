/*!
 * @author bintjeman
 * @date 16.06.25
 * @name ICoreEventHandler.hpp
 */
#ifndef ICOREEVENTHANDLER_HPP
#define ICOREEVENTHANDLER_HPP
#pragma once
#include <memory>
#include "i_event_listener.hpp"

namespace bnjkit {
    namespace core {
        class Core;
    }

    namespace event {
        class ICoreEventHandler : public IEventListener {
        public:
            virtual ~ICoreEventHandler() override;
            virtual void set_core(core::Core *core);

        protected:
            core::Core *m_core;
            std::shared_ptr<spdlog::logger> m_logger;
        };

    } // event
} // bnjkit
#endif //ICOREEVENTHANDLER_HPP
