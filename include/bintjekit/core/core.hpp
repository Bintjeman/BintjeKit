/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.hpp
 */
#ifndef CORE_HPP
#define CORE_HPP
#pragma once
#include <memory>
// #include "bintjekit/window/i_main_window.hpp"
// #include "bintjekit/event_manager/i_event_manager.hpp"
namespace bnjkit {
    namespace window {
        class IMainWindow;
    } // window
    namespace event {
        class IEventManager;
    } // event
    namespace core {
        class Core {
        public:
            Core();
            ~Core();
            void set_modules(std::unique_ptr<window::IMainWindow> window,
                             std::unique_ptr<event::IEventManager> event_manager);
            void run();

        private:
            std::unique_ptr<window::IMainWindow> m_main_window;
            std::unique_ptr<event::IEventManager> m_event_manager;

        public:
            Core(const Core &) = delete;
            Core &operator=(const Core &) = delete;
        };
    } // core
} // bnjkit
#endif //CORE_HPP
