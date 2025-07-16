/*!
 * @author bintjeman
 * @date 26.06.25
 * @name application.cpp
 */

#include "application.hpp"
// Third
#include <spdlog/spdlog.h>
// Bintjekit
#include <bintjekit/core.hpp>
#include <bintjekit/logger.hpp>
#include <bintjekit/configuration/settings.hpp>
#include <bintjekit/configuration/json_adapter.hpp>
// Evobot
#include "module.hpp"
#include "defaults_options.hpp"

namespace evo::app {
    Application::Application(const int argc, const char** argv): m_argv(argv) {
        opt::Option::make_options();
        parse_args(argc, argv);
    }
    Application::~Application() {
        m_logger->info("Application: destroyed");
    }
    void Application::init() {
        init_logger();
        m_logger = bnjkit::core::Logger::get_logger(bnjkit::literals::logger::APP);
        m_logger->critical("Working dir: {}", std::filesystem::current_path().c_str());
        m_logger->info("Application: created");
        m_logger->info("Application: initializing core");
        auto core = bnjkit::core::CoreBuilder()
                .set<engine::EvobotEngine>()
                .set<renderer::ImGuiRenderer>()
                .set<renderer::EvobotRenderer>()
                .set<renderer::Renderer>()
                .set<event::EventManager>()
                .set<window::Window>()
                .build();
        m_core = std::move(core);
    }

    void Application::configure() {
        using namespace bnjkit::core;
        m_logger->info("Application: configuring core");
        m_core->configure("evobot.json");
        auto& settings = m_core->settings();
        Logger::get_logger(logger_names::APP)->set_level(
            settings.get_or_set("/Application/Logger/App logger level", DEFAULT_LOGGER_LEVEL));
        Logger::get_logger(logger_names::CORE)->set_level(
            settings.get_or_set("/Application/Logger/Core logger level", DEFAULT_LOGGER_LEVEL));
        Logger::get_logger(logger_names::ENGINE)->set_level(
            settings.get_or_set("/Application/Logger/Engine logger level",
                                DEFAULT_LOGGER_LEVEL));
        Logger::get_logger(logger_names::CONFIGURATION)->set_level(
            settings.get_or_set("/Application/Logger/Conf logger level", DEFAULT_LOGGER_LEVEL));
        Logger::get_logger(logger_names::EVENT)->set_level(
            settings.get_or_set("/Application/Logger/Event logger level",
                                DEFAULT_LOGGER_LEVEL));
        Logger::get_logger(logger_names::WINDOW)->set_level(
            settings.get_or_set("/Application/Logger/Window logger level",
                                DEFAULT_LOGGER_LEVEL));
        Logger::get_logger(logger_names::RENDERER)->set_level(
            settings.get_or_set("/Application/Logger/Renderer logger level",
                                DEFAULT_LOGGER_LEVEL));
        Logger::get_logger(logger_names::ENTITY)->set_level(DEFAULT_ENTITY_LOGGER_LEVEL);
        m_core->set_engine_frequency(settings.get_or_set("/Application/Engine/Frequency", 60u));
        m_core->set_renderer_frequency(
            settings.get_or_set("/Application/Renderer/Frequency", 60u));
        m_core->set_window_frequency(settings.get_or_set("/Application/Window/Frequency", 60u));
    }
    void Application::run() {
        m_logger->info("Application: running core");
        m_core->run();
        update_config();
        m_core->save_settings();
    }
    void Application::parse_args(int argc, const char** argv) {
        std::vector<std::string> args;
        if (argc > 1) {
            for (int i = 1; i < argc; ++ i) {
                args.emplace_back(argv[i]);
            }
        }
        for (const auto& arg: args) {
            switch (const auto& opt = opt::Option::parse_arg(arg); opt.options) {
                case opt::EnumOptions::DEBUG:
                    break;
                case opt::EnumOptions::CLION: {
                    auto& workdir_option = opt::Option::parse_arg(
                        "--workdir=/home/bintjeman/CLionProjects/evobot/workdir");
                    workdir_option.forced = true;
                    break;
                }
                case opt::EnumOptions::WORKDIR:
                    break;
            }
            for (auto& enum_option: opt::Option::effectives_options) {
                auto& option = opt::Option::get_option(enum_option);
                switch (enum_option) {
                    case opt::EnumOptions::DEBUG:
                        break;
                    case opt::EnumOptions::CLION: {
                        break;
                    }
                    case opt::EnumOptions::WORKDIR: {
                        std::filesystem::path workdir_path(option.value);
                        std::filesystem::current_path(workdir_path);
                    }
                    break;
                }
            }
        }
    }
    void Application::init_logger() {
        using namespace bnjkit::core;
        Logger::get_logger(logger_names::APP)->set_level(DEFAULT_LOGGER_LEVEL);
        Logger::get_logger(logger_names::CORE)->set_level(DEFAULT_CORE_LOGGER_LEVEL);
        Logger::get_logger(logger_names::ENGINE)->set_level(DEFAULT_ENGINE_LOGGER_LEVEL);
        Logger::get_logger(logger_names::CONFIGURATION)->set_level(DEFAULT_CONF_LOGGER_LEVEL);
        Logger::get_logger(logger_names::EVENT)->set_level(DEFAULT_EVENT_LOGGER_LEVEL);
        Logger::get_logger(logger_names::WINDOW)->set_level(DEFAULT_WINDOW_LOGGER_LEVEL);
        Logger::get_logger(logger_names::RENDERER)->set_level(DEFAULT_RENDERER_LOGGER_LEVEL);
    }
    void Application::update_config() {
        using namespace bnjkit::core;
        auto& settings = m_core->settings();
        settings.set("/Application/Logger/App logger level",
                     Logger::get_logger(logger_names::APP)->level());
        settings.set("/Application/Logger/Core logger level",
                     Logger::get_logger(logger_names::CORE)->level());
        settings.set("/Application/Logger/Engine logger level",
                     Logger::get_logger(logger_names::ENGINE)->level());
        settings.set("/Application/Logger/Conf logger level",
                     Logger::get_logger(logger_names::CONFIGURATION)->level());
        settings.set("/Application/Logger/Event logger level",
                     Logger::get_logger(logger_names::EVENT)->level());
        settings.set("/Application/Logger/Window logger level",
                     Logger::get_logger(logger_names::WINDOW)->level());
        settings.set("/Application/Logger/Renderer logger level",
                     Logger::get_logger(logger_names::RENDERER)->level());
        settings.set("/Application/Engine/Frequency", m_core->engine_frequency());
        settings.set("/Application/Renderer/Frequency", m_core->renderer_frequency());
        settings.set("/Application/Window/Frequency", m_core->window_frequency());
    }
}
