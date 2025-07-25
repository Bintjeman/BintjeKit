/*!
 * @author bintjeman
 * @date 22.07.25
 * @name initialisation.cpp
 */
#include "initializer.hpp"
#include <bintjekit/core/common.hpp>
#include <bintjekit/logger/logger.hpp>
#include <bintjekit/configuration/settings.hpp>
#include <bintjekit/configuration/json_adapter.hpp>
#include "common.hpp"

namespace evo::initializer {
    constexpr auto LOGGER_DEFAULT_LEVEL = spdlog::level::info;
#ifdef NDEBUG
    constexpr auto LOGGER_DEFAULT_LEVEL_BEFORE_INIT = spdlog::level::info;
#else
    constexpr auto LOGGER_DEFAULT_LEVEL_BEFORE_INIT = spdlog::level::trace;
#endif

    int Initializer::initialise(int argc, char** argv) {
        auto working_dorectory = std::filesystem::current_path();
        std::vector<std::string_view> arguments{argv, argv + argc};
        if (arguments.size() > 1) {
            for (auto argument: arguments) {
                if (argument == "--clion") {
                    working_dorectory = "/home/bintjeman/CLionProjects/evobot/workdir";
                    if (!std::filesystem::exists(working_dorectory)) {
                        std::filesystem::create_directory(working_dorectory);
                    }
                }
            }
        }
        std::filesystem::current_path(working_dorectory);
        bnjkit::logger::Logger::initialize(common::literals.default_log_file_name, LOGGER_DEFAULT_LEVEL_BEFORE_INIT);
        const auto logger = bnjkit::logger::Logger::get_logger(bnjkit::literals::logger::APP);
        logger->info("Application initialized");
        logger->trace("Working directory: {}", working_dorectory.string());
        return 0;
    }
    void Initializer::configure(bnjkit::conf::Settings& settings) {
        auto logger_settings = settings.
                create_child(nlohmann::json::json_pointer(common::settings_child.logger));
        for (auto logger: bnjkit::literals::logger_enum) {
            const auto logger_level = logger_settings.
                    get_or_set(std::string{"/" + logger}, LOGGER_DEFAULT_LEVEL);
            bnjkit::logger::Logger::get_logger(logger)->set_level(logger_level);
        }
    }
    void Initializer::on_quit(bnjkit::conf::Settings& settings) {
        auto logger_settings = settings.create_child(nlohmann::json::json_pointer(common::settings_child.logger));
        for (const auto& logger: bnjkit::literals::logger_enum) {
            bnjkit::logger::Logger::get_logger(logger)->flush();
            const auto logger_level = bnjkit::logger::Logger::get_logger(logger)->level();
            logger_settings.set(std::string{"/" + logger}, logger_level);
        }
    }
}
