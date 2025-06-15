/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"
#include "bintjekit/renderer/i_bnjkit_imgui.hpp"

namespace bnjkit::window {
    IMainWindow::IMainWindow() {
        m_logger = core::Logger::get_logger(core::module_names::WINDOW);
        m_logger->info("Constructor of IMainWindow");
    }

    IMainWindow::~IMainWindow() noexcept {
        m_logger->info("Destructor of IMainWindow");
        renderer::IImGuiRenderer::shutdown();
    }

    void IMainWindow::initialise() {
        m_logger->info("Initialising IMainWindow");
    }

    void IMainWindow::show() {
        m_logger->info("Showing IMainWindow");
    }

    void IMainWindow::on_sfml_event(const sf::Event &event) {
        if (event.is<sf::Event::Closed>()) {
            close();
        }
    }
}
