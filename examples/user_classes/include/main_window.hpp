/*!
 * @author bintjeman
 * @date 11.06.25
 * @name main_window.hpp
 */
#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#pragma once
#include <bintjekit/window/i_main_window.hpp>
namespace usr {
    class MainWindow : public bnjkit::window::IMainWindow {
    public:
        MainWindow();
        ~MainWindow() override;
        void show() override;
        void initialise() override;
        void configure() override;
        void on_sfml_event(const sf::Event &event) override;
        [[nodiscard]] std::string name() const override;
    }; // MainWindow
} // usr
#endif //MAIN_WINDOW_HPP
