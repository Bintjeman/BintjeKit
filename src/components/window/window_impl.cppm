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
// #include <string>
#include <SFML/Window/VideoMode.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/detail/json_pointer.hpp>
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
        settings_ = settings;
    }

    void Window::initialize() {
        LOGGER->info("Window::initialize()");
        start_title_ = settings_.get<std::string>("/Title"_json_pointer, "proutproutprout");
        LOGGER->info("start_title_ : {}", start_title_);
        settings_.set<std::string>("/Title2"_json_pointer, "titre2");
        start_title_ = settings_.get<std::string>("/Title2"_json_pointer,"?" );
        LOGGER->info("start_title_ : {}", start_title_);
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

}
