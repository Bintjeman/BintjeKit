/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/configuration/json_adapter.hpp"

namespace bnjkit::window {
    IMainWindow::IMainWindow() {
        m_logger = core::Logger::get_logger(literals::logger::WINDOW);
        m_logger->info("Constructor of IMainWindow");
    }

    IMainWindow::~IMainWindow()  {
        m_logger->info("Destructor of IMainWindow");
    }

    void IMainWindow::initialise() {
        m_logger->trace("Initialising IMainWindow");
    }

    void IMainWindow::configure() {
        m_logger->trace("Configure IMainWindow");
    }

    void IMainWindow::show() {
        m_logger->trace("Showing IMainWindow");
        create(sf::VideoMode({800, 600}),"SFML window");
    }

    void IMainWindow::on_sfml_event(const sf::Event& event) {
        if (event.is<sf::Event::Closed>()) {
            close();
        }
    }

    void IMainWindow::close() {
        m_logger->info("Closing IMainWindow");
        RenderWindow::close();
    }

    void IMainWindow::on_quit() {
        m_logger->info("Quitting IMainWindow");
        IModule::on_quit();
    }
}
