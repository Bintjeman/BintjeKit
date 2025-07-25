/*!
 * @author bintjeman
 * @date 23.07.25
 * @name main_window.cpp
 */
#include "main_window.hpp"
#include <spdlog/logger.h>
#include <bintjekit/configuration/json_adapter.hpp>
namespace evo::window {
    MainWindow::MainWindow() {
        m_logger->info("{} Created", name());
    }
    MainWindow::~MainWindow() {
        m_logger->info("{} Destroyed", name());
    }
    void MainWindow::show() {
        sf::Vector2u size{1280, 720};
        sf::Vector2i position{80, 80};
        std::string title = name();
        m_logger->trace("{} Showing", name());
        size = m_settings.get_or_set("/Size", size);
        position = m_settings.get_or_set("/Position", position);
        title = m_settings.get_or_set("/Title", title);
        create(sf::VideoMode{size}, title, sf::Style::Default);
        setPosition(position);
        on_show();
    }
    void MainWindow::on_quit() {
        m_settings.set("/Size", getSize());
        m_settings.set("/Position", getPosition());
    }
    std::string MainWindow::name() const {
        return "Evobot Main Window";
    }
} // evo
