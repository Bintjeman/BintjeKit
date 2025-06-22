/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"
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
        m_logger->info("Initialising IMainWindow");
    }

    void IMainWindow::configure() {
        m_logger->info("Configure IMainWindow");
    }

    void IMainWindow::show() {
        m_logger->info("Showing IMainWindow");
    }

    void IMainWindow::on_sfml_event(const sf::Event& event) {
        if (event.is<sf::Event::Closed>()) {
            close();
        }
    }
    void IMainWindow::close() {
        m_logger->info("Closing IMainWindow");
        sf::Vector2u size = getSize();
        sf::Vector2i pos = getPosition();
        m_settings.set("/Size"_json_pointer, size);
        m_settings.set("/Position"_json_pointer, pos);
        RenderWindow::close();
    }
}
