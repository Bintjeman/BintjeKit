/*!
 * @file window_impl.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <iostream>
#include <SFML/Window/VideoMode.hpp>
export module window:impl;
import :interface;
import logger;
namespace bik::window {
    Window::Window() {
        logger::getLogger()->info("Window::Window()");
    }

    Window::~Window() {
        logger::getLogger()->info("Window::~Window()");
    }

    void Window::configure() {
    }

    void Window::initialize() {
        start_title_ = "window";
        start_size_ = {200, 200};
    }

    void Window::open() {
        constexpr auto style = sf::Style::Titlebar | sf::Style::Close;
        auto mode = sf::VideoMode{start_size_, 32};
        create(mode, start_title_, style);
        setPosition(start_pos_);
    }

    void Window::finalize() {
    }

    void Window::hw() {
        std::cout << "Je suis window de bintjeKit !" << std::endl;
    }
}
