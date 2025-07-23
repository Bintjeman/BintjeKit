/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_main_window.cpp
 */
#include "bintjekit/window/default_main_window.hpp"
#include "spdlog/logger.h"
namespace bnjkit::window {
    DefaultMainWindow::DefaultMainWindow(): IMainWindow() {
        m_logger->warn("DefaultMainWindow created");
    }
    DefaultMainWindow::~DefaultMainWindow() {
        m_logger->warn("DefaultMainWindow destroyed");
    }
    std::string DefaultMainWindow::name() const {
        return "DefaultMainWindow";
    }
    void DefaultMainWindow::show() {
        m_logger->warn("DefaultMainWindow show");
        create(sf::VideoMode{{200,200}}, "DefaultMainWindow");
        IMainWindow::show();
    }
}
