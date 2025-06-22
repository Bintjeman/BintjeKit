/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.hpp
 */
#ifndef I_MAIN_WINDOW_HPP
#define I_MAIN_WINDOW_HPP
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <spdlog/fwd.h>
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"
#include "bintjekit/configuration/node.hpp"
namespace bnjkit {
    namespace window {
        class IMainWindow : public core::IModule, public sf::RenderWindow, public event::IEventListener {
        public:
            IMainWindow();
            ~IMainWindow() noexcept override;
            void initialise() override;
            void configure() override;
            virtual void show() = 0;
            void on_sfml_event(const sf::Event& event) override;

        protected:
            std::shared_ptr<spdlog::logger> m_logger;

        private:
        };
    } // bnjkit
} // window
#endif // I_MAIN_WINDOW_HPP
