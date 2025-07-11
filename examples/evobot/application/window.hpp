/*!
 * @author bintjeman
 * @date 03.07.25
 * @name window.hpp
 */

#ifndef  EVO_WINDOW_HPP
#define  EVO_WINDOW_HPP
#pragma once
#include <bintjekit/window/i_main_window.hpp>

namespace evo::window {
    class Window final : public bnjkit::window::IMainWindow {
    public:
        Window();
        ~Window() override;
        void show() override;
        [[nodiscard]] std::string name() const override;
        void close() override;
        void on_sfml_event(const sf::Event& event) override;
    };
}

#endif // EVO_WINDOW_HPP
