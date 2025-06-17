/*!
 * @author bintjeman
 * @date 16.06.25
 * @name i_core_event_handler.cpp
 */
#include "bintjekit/event_manager/i_core_event_handler.hpp"

#include "bintjekit/core/logger.hpp"

bnjkit::event::ICoreEventHandler::ICoreEventHandler() {
    m_logger = core::Logger::get_logger("EVENT");
}

bnjkit::event::ICoreEventHandler::~ICoreEventHandler() = default;

void bnjkit::event::ICoreEventHandler::set_core(core::Core *core) {
    m_logger->info("ICoreEventHandler: Setting core");
    m_core = core;
}
