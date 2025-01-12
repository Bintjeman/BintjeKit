/*!
 * @file ui_impl.cppm
 * @author bintjeman
 * @date 07.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <SFML/Window/Event.hpp>
#include "tools/logger/logger_define.hpp"
export module bik.ui:impl;
import :interface;
import bik.window;
import bik.common;
import bik.logger;
import bik.renderer;
import bik.playground;
namespace bik::ui {
    BaseUI::BaseUI(window::BaseWindow &window, renderer::BaseRenderer &renderer,
                   playground::BasePlayGround &playground) : window_(window), renderer_(renderer),
                                                             playground_(playground) {
        LOGGER->info("UI::UI()");
    }

    BaseUI::~BaseUI() {
        LOGGER->info("UI::~UI()");
    }

    void BaseUI::configure() {
    }

    void BaseUI::initialize() {
    }

    void BaseUI::update() {
        event_handler();
    }

    void BaseUI::finalize() {
    }

    void BaseUI::set_action_receiver(common::BaseIActionReceiver *action_receiver) {
        action_receiver_ = action_receiver;
    }

    void BaseUI::event_handler() {
        while (const std::optional event = window_.pollEvent()) {
            if (event.has_value()) {
            }
            if (event->is<sf::Event::Closed>()) {
                on_close();
            } else if (const auto *key_event = event->getIf<sf::Event::KeyPressed>()) {
                key_pressed(*key_event);
            } else if (const auto *resize_event = event->getIf<sf::Event::Resized>()) {
                resized(*resize_event);
            } else if (const auto *scroll_event = event->getIf<sf::Event::MouseWheelScrolled>()) {
                mouse_scrolled(*scroll_event);
            }
        }
    }

    void BaseUI::on_close() {
        action_receiver_->on_close_window();
    }

    void BaseUI::key_pressed(const sf::Event::KeyPressed &key_event) {
        LOGGER->trace("Touche appuyée");
        switch (key_event.scancode) {
            case sf::Keyboard::Scancode::Q:
                if (key_event.control) {
                    on_close();
                }
                break;
        }
    }

    void BaseUI::resized(const sf::Event::Resized &size_event) {
    }

    void BaseUI::mouse_scrolled(const sf::Event::MouseWheelScrolled &scroll_event) {
    }
}
