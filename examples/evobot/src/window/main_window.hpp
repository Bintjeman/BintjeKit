/*!
 * @author bintjeman
 * @date 23.07.25
 * @name main_window.hpp
 */
#ifndef EVOBOT_WINDOW_MAIN_WINDOW_HPP
#define EVOBOT_WINDOW_MAIN_WINDOW_HPP
#pragma once
#include <bintjekit/window/i_main_window.hpp>
namespace evo::window {
    class
            MainWindow final : public bnjkit::window::IMainWindow {
    public:
        MainWindow();
        ~MainWindow() override;
        void show() override;
        void on_quit() override;
        [[nodiscard]] std::string name() const override;
    };
}
#endif
