/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.cpp
 */
#include "bintjekit/window/i_main_window.hpp"
#include <imgui-SFML.h>
#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"

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

    void IMainWindow::initialise_imgui() {
        m_logger->info("Initialising ImGui");
        if (!ImGui::SFML::Init(*this)) {
            throw std::runtime_error("Failed to initialise ImGui");
        }
    }

    void IMainWindow::show() {
        m_logger->info("Showing IMainWindow");
        initialise_imgui();
    }

    void IMainWindow::on_sfml_event(const sf::Event &event) {
        ImGui::SFML::ProcessEvent(*this, event);
    }
}
