/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/core/common.hpp"
#include "../../include/bintjekit/logger/logger.hpp"
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
        sf::Vector2u size = getSize();
        sf::Vector2i pos = getPosition();
        m_settings.set("/Size"_json_pointer, size);
        m_settings.set("/Position"_json_pointer, pos);
        auto settings_json = m_settings.get_json();
        m_logger->trace("Window settings: {}", settings_json.dump(2));
        m_logger->trace("Window settings root: {}", m_settings.branch_str());
        RenderWindow::close();
    }
    std::string IMainWindow::name() const {
        return "IMainWindow";
    }
}
