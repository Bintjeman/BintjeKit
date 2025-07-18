/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.hpp
 */
#ifndef BNJKIT_WINDOW_I_MAIN_WINDOW_HPP
#define BNJKIT_WINDOW_I_MAIN_WINDOW_HPP
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "bintjekit/core/i_module.hpp"

namespace bnjkit::window {
    class IMainWindow : public core::IModule, public sf::RenderWindow {
    public:
        enum class WindowState {
            RUNNING,
            CLOSING,
            CLOSED
        };
        IMainWindow();
        ~IMainWindow() override;
        void initialise() override;
        void configure() override;
        virtual void show();
        void close() override ;
        void on_quit() override;
        [[nodiscard]] WindowState state() const;
        void request_close();
        bool is_running() const;
    private:
        WindowState m_state{WindowState::CLOSED};
    };
}
#endif // BNJKIT_WINDOW_I_MAIN_WINDOW_HPP
