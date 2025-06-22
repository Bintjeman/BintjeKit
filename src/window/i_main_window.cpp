/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"
// #include "bintjekit/renderer/i_bnjkit_imgui.hpp"
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
        sf::Vector2i position = m_settings.get("/Position"_json_pointer, sf::Vector2i{200, 200});
        sf::Vector2u size = m_settings.get("/Size"_json_pointer, sf::Vector2u{1000, 1000});
        std::string title = m_settings.get("/Title"_json_pointer, std::string("GOL"));
        setPosition(position);
        setSize(size);
        setTitle(title);
    }

    void IMainWindow::show() {
        m_logger->info("Showing IMainWindow");
    }

    void IMainWindow::on_sfml_event(const sf::Event& event) {
        if (event.is<sf::Event::Closed>()) {
            close();
        }
    }
}
