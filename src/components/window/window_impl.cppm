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
#include <nlohmann/json.hpp>
#include <nlohmann/detail/json_pointer.hpp>
#include <iostream>
#include <SFML/Window/VideoMode.hpp>
#include <utility>
export module window:impl;
import :interface;
import logger;
import settings_manager;
namespace bik::window {
    Window::Window() {
        logger::getLogger()->info("Window::Window()");
    }

    Window::~Window() {
        logger::getLogger()->info("Window::~Window()");
    }

    void Window::configure(const config::Node& settings) {
        settings_ = settings;
    }

    void Window::initialize() {
        std::cout << "Settings node number: " << settings_.node_number() << std::endl;
        std::cout << settings_.raw().dump(4) << std::endl;
        start_title_ = settings_.get_or_set<std::string>("/Title"_json_pointer, "proutproutprout");
        start_pos_={200, 200};
        start_size_={200, 200};
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
