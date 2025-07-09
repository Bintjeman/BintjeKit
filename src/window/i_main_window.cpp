/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/configuration/sfml_json_adapter.hpp"

namespace bnjkit::window {
    IMainWindow::IMainWindow() {
        m_logger = core::Logger::get_logger(core::module_names::WINDOW);
        m_logger->info("Constructor of IMainWindow");
    }

    IMainWindow::~IMainWindow() noexcept {
        m_logger->info("Destructor of IMainWindow");
    }

    void IMainWindow::initialise() {
        m_logger->debug("Initialising IMainWindow");
    }

    void IMainWindow::configure() {
        m_logger->debug("Configure IMainWindow");
    }

    void IMainWindow::show() {
        m_logger->debug("Showing IMainWindow");
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

    std::string IMainWindow::name() const {
        return "IMainWindow";
    }

    void IMainWindow::on_quit() {
        IModule::on_quit();
    }
}
