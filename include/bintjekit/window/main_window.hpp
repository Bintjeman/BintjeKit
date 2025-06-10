/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.hpp
 */
#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

namespace bnjkit {
    class MainWindow : protected sf::RenderWindow {
    public:
        MainWindow();
        ~MainWindow();
        void open();
    private:
    };
}
#endif //MAIN_WINDOW_HPP
