/*!
 * @author bintjeman
 * @date 19.07.25
 * @name application.cpp
 */
#include "application.hpp"
#include <bintjekit/logger.hpp>
#include <bintjekit/core.hpp>
#include <bintjekit/configuration/settings.hpp>
#include "window/window.hpp"

namespace bil {
    Application::Application() = default;
    Application::~Application() = default;
    void Application::initialisation() {
        bnjkit::logger::Logger::initialize(spdlog::level::info);
        bnjkit::logger::Logger::set_module_level(bnjkit::literals::logger::LOG, spdlog::level::trace);
        bnjkit::logger::Logger::set_module_level(bnjkit::literals::logger::CONFIGURATION, spdlog::level::trace);
        m_logger = bnjkit::logger::Logger::get_logger(bnjkit::literals::logger::APP);
        m_logger->info("Application initialised");
        m_core = bnjkit::core::CoreBuilder()
                .set<Window>()
                .build();
        m_core->initialise();
        configuration();
    }
    void Application::configuration() {
        auto settings = bnjkit::conf::Settings::create(std::filesystem::path("billard.json"));
        m_core->set_settings(settings);
        m_core->configure();
        m_logger->info("Application configured");
    }
    void Application::run() {
        m_logger->info("Application started");
        auto& settings = m_core->settings();
        m_core->run();
        settings.save_to_file();
        m_logger->info("Application stopped");
    }
    std::shared_ptr<spdlog::logger> Application::logger() {
        return m_logger;
    }
} // bil
