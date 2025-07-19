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
        m_logger = logger::Logger::get_logger(literals::logger::WINDOW);
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
        std::string title = name();
        create(sf::VideoMode({800, 600}), title);
        on_show();
    }
    void IMainWindow::close() {
        m_logger->info("Closing IMainWindow");
        m_state = WindowState::CLOSED;
        RenderWindow::close();
    }
    void IMainWindow::on_quit() {
        m_logger->info("Quitting IMainWindow");
        IModule::on_quit();
    }
    IMainWindow::WindowState IMainWindow::state() const {
        return m_state;
    }
    void IMainWindow::request_close() {
        m_logger->info("Requesting close of IMainWindow");
        m_state = WindowState::CLOSING;
    }
    bool IMainWindow::is_running() const {
        return m_state == WindowState::RUNNING;
    }
    void IMainWindow::on_show() {
        m_state = WindowState::RUNNING;
    }
}
