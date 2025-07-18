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

    IMainWindow::~IMainWindow() {
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
        create(sf::VideoMode({800, 600}), "SFML window");
    }

    void IMainWindow::close() {
        m_logger->info("Closing IMainWindow");
        RenderWindow::close();
    }
    bool IMainWindow::quit(bool quit) {
       if (quit) {
            m_on_quit = true;
        }
        return m_on_quit;
    }
    void IMainWindow::on_quit() {
        m_logger->info("Quitting IMainWindow");
        IModule::on_quit();
        close();
    }
}
