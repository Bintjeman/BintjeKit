/*!
 * @author bintjeman
 * @date 19.07.25
 * @name window.hpp
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP
#pragma once
#include <bintjekit/window/default_main_window.hpp>

namespace bil {
    class Window : public bnjkit::window::DefaultMainWindow {
    public:
        Window();
        ~Window();
        void show() override;
        void on_quit() override;
        [[nodiscard]] std::string name() const override;
    };
} // bil

#endif //WINDOW_HPP
