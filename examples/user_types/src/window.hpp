/*!
 * @author bintjeman
 * @date 18.07.25
 * @name window.hpp
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP
#pragma once
#include <bintjekit/window/default_main_window.hpp>
namespace utypes {
    class Window : public bnjkit::window::DefaultMainWindow {
        public:
            Window();
            ~Window();
    };
} // utypes

#endif //WINDOW_HPP
