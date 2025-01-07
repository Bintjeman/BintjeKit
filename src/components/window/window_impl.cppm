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
export module bik.window:impl;
import :interface;
import bik.logger;
import bik.settings;
namespace bik::window {
    BaseWindow::BaseWindow() {
        LOGGER->info("Window::Window()");
    }

    BaseWindow::~BaseWindow() {
        LOGGER->info("Window::~Window()");
    }

    void BaseWindow::configure(const config::Child &settings) {
        LOGGER->info("Window::configure()");
        settings_ = settings;
        settings_.set("/Title"_json_pointer, "titre");
    }

    void BaseWindow::initialize() {
        LOGGER->info("Window::initialize()");
        settings_.set("/Title2"_json_pointer, "titre2");
        start_title_ = settings_.get_or_set("/Title"_json_pointer, std::string("BaseWindow"));
        start_pos_ = settings_.get_or_set("/Position"_json_pointer, sf::Vector2i(100, 100));
        start_size_ = settings_.get_or_set("/Size"_json_pointer, sf::Vector2u(200, 200));
    }

    void BaseWindow::open() {
        LOGGER->info("Window::open()");
        const auto style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
        const auto mode = sf::VideoMode{start_size_, 32};
        create(mode, start_title_, style);
        setPosition(start_pos_);
    }

    void BaseWindow::update() {
        update_inner();
    }

    void BaseWindow::pre_rendering() {
        clear();
    }

    void BaseWindow::rendering() {
        display();
    }

    void BaseWindow::post_rendering() {

    }

    void BaseWindow::finalize() {
        LOGGER->info("Window::finalize()");
        const sf::Vector2i position = getPosition();
        const auto size = getSize();
        LOGGER->trace("Position : {}", position);
        settings_.set("/Position"_json_pointer, position);
        settings_.set("/Size"_json_pointer, size);
    }

    void BaseWindow::update_inner() {
        pre_rendering();
        rendering();
        post_rendering();
    }
}
