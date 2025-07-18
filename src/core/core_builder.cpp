/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.cpp
 */
#include "bintjekit/core/core_builder.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/core/core.hpp"
#include "bintjekit/renderer/i_imgui_renderer.hpp"
#include "bintjekit/renderer/i_renderer.hpp"

namespace bnjkit::core {
    CoreBuilder::CoreBuilder() {
        m_logger = Logger::get_logger(literals::logger::CORE);
        m_logger->info("Constructor of CoreBuilder");
    }
    CoreBuilder::~CoreBuilder() {
        // m_logger->info("Destructor of CoreBuilder");
    };
    std::unique_ptr<Core> CoreBuilder::build() {
        m_logger->info("Building Core");
        auto core = std::make_unique<Core>();
        m_modules_tmp.check_modules(true);
        m_modules_tmp.renderer().set_modules(& m_modules_tmp);
        m_modules_tmp.imgui_renderer().set_modules(& m_modules_tmp);
        core->set_modules(std::move(m_modules_tmp));
        return core;
    }
} // bnjkit::core
