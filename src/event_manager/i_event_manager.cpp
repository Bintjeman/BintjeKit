/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_event_manager.cpp
 */
#include "bintjekit/event_manager/i_event_manager.hpp"
#include "bintjekit/logger.hpp"

namespace bnjkit::event {
    IEventManager::IEventManager(): m_modules(nullptr) {
        m_logger = core::Logger::get_logger(literals::logger::EVENT);
        m_logger->info("Constructor of IEventManager");
    }
    IEventManager::~IEventManager() {
        m_logger->info("Destructor of IEventManager");
    }
    void IEventManager::initialise() {
        m_logger->trace("Initialising IEventManager");
        IModule::initialise();
    }
    void IEventManager::configure() {
        m_logger->trace("Configuring IEventManager");
        IModule::configure();
    }
    void IEventManager::on_quit() {
        m_logger->info("Quitting IEventManager");
        IModule::on_quit();
    }
    void IEventManager::set_modules(core::ModuleSet* modules) {
        m_logger->trace("Setting modules");
        m_modules = modules;
    }
    void IEventManager::process_events() {}
}
