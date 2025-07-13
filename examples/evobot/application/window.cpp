/*!
 * @author bintjeman
 * @date 03.07.25
 * @name window.cpp
 */

#include "window.hpp"
#include <bintjekit/configuration/sfml_json_adapter.hpp>
#include <bintjekit/event_manager/event_helper.hpp>

namespace evo::window {
    Window::Window() {
        m_logger->info("Window: created");
    }
    Window::~Window() {
        m_logger->info("Window: destroyed");
    }
    void Window::show() {
        m_logger->info("Window: showing");
        sf::Vector2u size = m_settings.get_or_set("/Size", sf::Vector2u{1700, 900});
        sf::Vector2i position = m_settings.get_or_set("/Position", sf::Vector2i{100, 100});
        std::string title = m_settings.get_or_set("/Title", std::string("Evobot"));
        create(sf::VideoMode(size, 32), title, sf::Style::Default);
        setPosition(position);
    }
    std::string Window::name() const {
        return "evo::window::Window";
    }
    void Window::close() {
        m_logger->info("Window: closing");
        sf::Vector2i position = getPosition();
        m_settings.set("/Position", position);
        sf::Vector2u size = getSize();
        m_settings.set("/Size", size);
        IMainWindow::close();
    }
    void Window::on_sfml_event(const sf::Event& event) {
        if (const auto& close_event = event.getIf<sf::Event::Closed>()) {
            close();
        }
        if (const auto& key_pressed = event.getIf<sf::Event::KeyPressed>()) {
            if (key_pressed->code == sf::Keyboard::Key::Q && bnjkit::event::ctrl()) {
                close();
            }
        }
    }
}
