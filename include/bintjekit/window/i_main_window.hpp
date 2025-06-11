/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.hpp
 */
#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "bintjekit/core/i_module.hpp"

namespace bnjkit::window {
    class IMainWindow : public core::IModule, public sf::RenderWindow {
    public:
        IMainWindow();
        ~IMainWindow() override;
        virtual void show() =0;

    private:
    };
} // bnjkit::window
#endif //MAIN_WINDOW_HPP
