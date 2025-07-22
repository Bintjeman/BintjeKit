/*!
 * @author bintjeman
 * @date 19.07.25
 * @name application.cpp
 */
#include "application.hpp"
#include <bintjekit/logger.hpp>
#include <bintjekit/core.hpp>
#include <bintjekit/configuration/settings.hpp>
#include <bintjekit/configuration/json_adapter.hpp>
#include "modules.hpp"
#include "renderer/renderer.hpp"

namespace bil {
    Application::Application() = default;
    Application::~Application() {
        m_logger->info("Application destroyed");
    }
    void Application::initialisation() {
        const auto settings = bnjkit::conf::Settings::create(std::filesystem::path("billard.json"));
        auto log_node = settings->create_child("/Log"_json_pointer);
        init_logger(log_node);
        m_logger->info("Application initialised");
        m_core = bnjkit::core::CoreBuilder()
                .set<Window>()
                .set<Billard>()
                .set<Renderer>()
                .set<EventManager>()
                .set<ImGuiRenderer>()
                .build();
        m_core->initialise();
        m_core->set_settings(settings);
        configuration();
    }
    void Application::configuration() {
        m_core->configure();
        m_logger->info("Application configured");
    }
    void Application::run() {
        m_logger->info("Application started");
        const auto& settings = m_core->settings();
        m_core->run();
        update_setting();
        settings.save_to_file();
        m_logger->info("Application stopped");
    }
    std::shared_ptr<spdlog::logger> Application::logger() {
        return m_logger;
    }
    void Application::update_setting() {
        m_logger->info("Update setting");
        const auto settings = m_core->settings();
        auto node = settings.create_child("/Log"_json_pointer);
        for (const auto& log_name: bnjkit::literals::logger_enum) {
            if (!log_name.empty()) {
                node.set({"/Log level/" + log_name}, bnjkit::logger::Logger::get_logger(log_name)->level());
            }
        }
    }
    void Application::init_logger(bnjkit::conf::Node& node) {
        constexpr auto default_level = spdlog::level::info;
        for (const auto& log_name: bnjkit::literals::logger_enum) {
            if (!log_name.empty()) {
                const auto log_level = node.get_or_set({"/Log level/" + log_name}, default_level);
                bnjkit::logger::Logger::set_module_level(log_name, log_level);
            }
        }
        m_logger = bnjkit::logger::Logger::get_logger(bnjkit::literals::logger::APP);
    }
} // bil
