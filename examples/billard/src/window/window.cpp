/*!
 * @author bintjeman
 * @date 19.07.25
 * @name window.cpp
 */
#include "window.hpp"
#include <spdlog/spdlog.h>
#include <bintjekit/configuration/json_adapter.hpp>
namespace bil {
    Window::Window() {
        m_logger->info("Window created");
    }
    Window::~Window() {
        m_logger->info("Window destroyed");
    }
    void Window::show() {
        const auto position = m_settings.get_or_set("/Position", sf::Vector2i{200, 200});
        const auto size = m_settings.get_or_set("/Size", sf::Vector2u{1000, 800});
        const auto title = m_settings.get_or_set("/Title", std::string("Billard"));
        create(sf::VideoMode{size}, title);
        setPosition(position);
        on_show();
    }
    void Window::on_quit() {
        DefaultMainWindow::on_quit();
        const auto position = getPosition();
        const auto size = getSize();
        m_settings.set("/Position", position);
        m_settings.set("/Size", size);
    }
    std::string Window::name() const {
        return "Billard window";
    }
} // bil
