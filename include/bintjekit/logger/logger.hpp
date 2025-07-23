/*!
 * @author bintjeman
 * @date 14.06.25
 * @name logger.hpp
 */

#ifndef BNJKIT_CORE_LOGGER_HPP
#define BNJKIT_CORE_LOGGER_HPP
#pragma once
#include <filesystem>
#include <memory>
#include <spdlog/spdlog.h>

namespace bnjkit::logger {
    class Logger {
    public:
        static void initialize(const std::filesystem::path& default_path = {},
                               const spdlog::level::level_enum& default_level = spdlog::level::info);
        static void shutdown();
        static std::shared_ptr<spdlog::logger> get_logger(const std::string& module_name);
        static void set_module_level(const std::string& module_name,
                                     spdlog::level::level_enum level);
        static void set_default_level(const spdlog::level::level_enum& level);
        static void set_log_path(const std::filesystem::path& path);
        static std::filesystem::path get_log_path();

    private:
        static std::shared_ptr<spdlog::logger> add_logger(const std::string& module_name,
                                                          const spdlog::level::level_enum& level);
        static spdlog::sink_ptr file_sink();
        static std::filesystem::path s_log_path;
        static std::unordered_map<std::string, std::shared_ptr<spdlog::logger> > s_loggers;
        static std::vector<spdlog::sink_ptr> s_sinks;
        static spdlog::level::level_enum s_default_level;
        static bool s_initialized;
    };
    static const char* LEVEL_ENUM[] = {
        spdlog::level::to_string_view(spdlog::level::trace).data(),
        spdlog::level::to_string_view(spdlog::level::debug).data(),
        spdlog::level::to_string_view(spdlog::level::info).data(),
        spdlog::level::to_string_view(spdlog::level::warn).data(),
        spdlog::level::to_string_view(spdlog::level::err).data(),
        spdlog::level::to_string_view(spdlog::level::critical).data()
    };
}
#endif // BNJKIT_CORE_LOGGER_HPP
