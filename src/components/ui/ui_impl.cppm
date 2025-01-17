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
#include "external/dear_imgui/imgui-SFML.h"
#include "tools/logger/logger_define.hpp"
export module bik.ui:impl;
import :interface;
import bik.window;
import bik.common;
import bik.logger;
import bik.renderer;
import bik.playground;
import bik.imgui_wrapper;
namespace bik::ui {
    BaseUI::BaseUI() {
        LOGGER->info("UI::UI()");
    }

    BaseUI::~BaseUI() {
        LOGGER->info("UI::~UI()");
    }

    void BaseUI::update() {
        event_handler();
    }

    void BaseUI::finalize() {
        LOGGER->info("UI::finalize()");
    }

    void BaseUI::set_action_receiver(common::BaseIActionReceiver *action_receiver) {
        LOGGER->debug("UI::set_action_receiver()");
        action_receiver_ = action_receiver;
    }

    void BaseUI::set_playground(const std::shared_ptr<playground::BasePlayGround>& playground) {
        LOGGER->debug("UI::set_playground()");
        playground_ = playground;
    }

    void BaseUI::set_renderer(const std::shared_ptr<renderer::BaseRenderer>& renderer) {
        LOGGER->debug("UI::set_renderer()");
        renderer_ = renderer;
    }

    void BaseUI::set_window(const std::shared_ptr<window::BaseWindow>& window) {
        LOGGER->debug("UI::set_window()");
        window_ = window;
    }

    void BaseUI::set_imgui_wrapper(const std::shared_ptr<imguiwrapper::BaseImGuiWrapper>& imgui_wrapper) {
        LOGGER->debug("UI::set_imgui_wrapper()");
        imgui_wrapper_ = imgui_wrapper;
    }

    void BaseUI::event_handler() {
        while (const std::optional event = window_->pollEvent()) {
            ImGui::SFML::ProcessEvent(*window_, *event);
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
        LOGGER->info("UI::on_close()");
        action_receiver_->on_close_window();
    }

    void BaseUI::key_pressed(const sf::Event::KeyPressed &key_event) {
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
