/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.cpp
 */
#include "bintjekit/core/core_builder.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/core/core.hpp"

namespace bnjkit::core {
    CoreBuilder::CoreBuilder() {
        m_logger = Logger::get_logger(literals::logger::CORE);
        m_logger->info("Constructor of CoreBuilder");
    }
    CoreBuilder::~CoreBuilder() {
        if (m_logger) {
            m_logger->info("Destructor of CoreBuilder");
        }
    };
    std::unique_ptr<Core> CoreBuilder::build() {
        m_logger->info("Building Core");
        auto core = std::make_unique<Core>();
        m_modules_tmp.check_modules(true);
        core->set_modules(std::move(m_modules_tmp));
        return core;
    }
} // bnjkit::core
