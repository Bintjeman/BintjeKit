/*!
 * @author bintjeman
 * @date 19.07.25
 * @name application.cpp
 */
#include "application.hpp"
#include <bintjekit/logger.hpp>
#include <bintjekit/core.hpp>
namespace bil {
    Application::Application() {}
    Application::~Application() {}
    void Application::initialisation() {
        bnjkit::core::Logger::initialize(spdlog::level::info);
        bnjkit::core::Logger::set_module_level(bnjkit::literals::logger::LOG, spdlog::level::trace);
        m_logger = bnjkit::core::Logger::get_logger(bnjkit::literals::logger::APP);
        m_logger->info("Application initialised");
        m_core = bnjkit::core::CoreBuilder()
        .build();
    }
    void Application::run() {
        m_logger->info("Application started");
        m_core->run();
        m_logger->info("Application stopped");
    }
    std::shared_ptr<spdlog::logger> Application::logger() {
        return m_logger;
    }
} // bil