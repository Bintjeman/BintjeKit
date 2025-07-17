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
    class IMainWindow : public core::IModule, public sf::RenderWindow{
    public:
        IMainWindow();
        ~IMainWindow() override;
        void initialise() override;
        void configure() override;
        virtual void show();
        void close() override;


    private:
        void on_quit() override;
    };
}
#endif // BNJKIT_WINDOW_I_MAIN_WINDOW_HPP
