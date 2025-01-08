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
export module bik.ui:impl;
import :interface;
import bik.window;
namespace bik::ui {
    BaseUI::BaseUI(bik::window::BaseWindow &window) : window_(window){
    }

    void BaseUI::configure() {
    }

    void BaseUI::initialize() {
    }

    void BaseUI::update() {
    }

    void BaseUI::finalize() {
    }

    void BaseUI::event_handler(sf::Event &event) {
    }
}
