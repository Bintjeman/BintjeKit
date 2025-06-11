/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.cpp
 */
#include "bintjekit/core/core_builder.hpp"
#include "bintjekit/core/core.hpp"
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/window/default_main_window.hpp"
namespace bnjkit::core {
    CoreBuilder &CoreBuilder::set_window_module(std::unique_ptr<window::IMainWindow> window) {
        m_window = std::move(window);
        return *this;
    }
    std::unique_ptr<Core> CoreBuilder::build() {
        auto core = std::make_unique<Core>();
        if (!m_window) {
            m_window.reset();
            m_window = std::make_unique<window::DefaultMainWindow>();
        }
        core->set_modules(std::move(m_window));
        return core;
    }
} // bnjkit::core
