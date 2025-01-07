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
#include <SFML/Window/VideoMode.hpp>
#include <nlohmann/json.hpp>
#include "tools/logger/logger_define.hpp"
export module window:impl;
import :interface;
import logger;
import settings;
namespace bik::window {
    Window::Window() {
        LOGGER->info("Window::Window()");
    }

    Window::~Window() {
        LOGGER->info("Window::~Window()");
    }

    void Window::configure(const config::Child& settings) {
        LOGGER->info("Window::configure()");
        settings_ = settings;
        settings_.set("/Title"_json_pointer, "titre");
    }

    void Window::initialize() {
        LOGGER->info("Window::initialize()");
        settings_.set("/Title2"_json_pointer, "titre2");
        start_title_ = settings_.get_or_set("/Title"_json_pointer,std::string("BaseWindow") );
        start_pos_ = settings_.get_or_set("/Position"_json_pointer,sf::Vector2i(100,100));
        start_size_= settings_.get_or_set("/Size"_json_pointer,sf::Vector2u(200,200));
    }

    void Window::open() {
        LOGGER->info("Window::open()");
        const auto style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
        const auto mode = sf::VideoMode{start_size_, 32};
        create(mode, start_title_, style);
        setPosition(start_pos_);
    }

    void Window::finalize() {
        LOGGER->info("Window::finalize()");
        auto position = getPosition();
        auto size = getSize();
        settings_.set("/Position"_json_pointer, position);
        settings_.set("/Size"_json_pointer, size);
    }

}
