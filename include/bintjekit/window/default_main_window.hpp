/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_main_window.hpp
 */
#ifndef BINTJEKIT_WINDOW_DEFAULT_MAIN_WINDOW_HPP
#define BINTJEKIT_WINDOW_DEFAULT_MAIN_WINDOW_HPP
#pragma once
#include "bintjekit/window/i_main_window.hpp"

namespace bnjkit::window {
    class DefaultMainWindow : public IMainWindow {
    public:
        DefaultMainWindow();
        ~DefaultMainWindow() override;
        [[nodiscard]] std::string name() const override;
    };
}
#endif //BINTJEKIT_WINDOW_DEFAULT_MAIN_WINDOW_HPP
