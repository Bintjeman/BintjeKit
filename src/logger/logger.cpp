/*!
 * @author bintjeman
 * @date 14.06.25
 * @name logger.cpp
 */
#include "bintjekit/logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "bintjekit/core/common.hpp"

namespace bnjkit::core {
    std::unordered_map<std::string, std::shared_ptr<spdlog::logger> > Logger::s_loggers;
    std::vector<spdlog::sink_ptr> Logger::s_sinks;
    spdlog::level::level_enum Logger::s_default_level = spdlog::level::info;
    bool Logger::s_initialized = false;
    void Logger::initialize(const spdlog::level::level_enum& level) {
        if (s_initialized) {
            s_loggers.at(literals::logger::LOG)->info("Logger already initialised");
            return;
        }
        s_default_level = level;
        spdlog::enable_backtrace(32);
        const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("%^[%T] [%-8l] [%-8n] : %v%$");
        s_sinks.push_back(console_sink);
        const auto file_sink = std::make_shared<
            spdlog::sinks::basic_file_sink_mt>("bnjkit.log", true);
        file_sink->set_pattern("[%T] [%-8l] [%-8n] : %v");
        s_sinks.push_back(file_sink);
        add_logger(bnjkit::literals::logger::LOG, s_default_level);
        s_initialized = true;
    }
    std::shared_ptr<spdlog::logger> Logger::get_logger(const std::string& module_name) {
        if (!s_initialized) {
            initialize();
        }
        if (const auto it = s_loggers.find(module_name); it != s_loggers.end()) {
            return it->second;
        }
        return add_logger(module_name, s_default_level);
    }
    void Logger::set_module_level(const std::string& module_name,
                                  const spdlog::level::level_enum level) {
        get_logger(module_name)->set_level(level);
    }
    void Logger::set_default_level(const spdlog::level::level_enum& level) {
        s_default_level = level;
    }
    std::shared_ptr<spdlog::logger> Logger::add_logger(const std::string& module_name,
                                                       const spdlog::level::level_enum& level) {
        auto logger = std::make_shared<spdlog::logger>(module_name, s_sinks.begin(),
                                                       s_sinks.end());
        spdlog::register_logger(logger);
        logger->set_level(level);
        s_loggers[module_name] = logger;
        logger->info("Logger \"{}\" initialised", module_name.c_str());
        if (module_name != literals::logger::LOG) {
            s_loggers.at(literals::logger::LOG)->info("Logger \"{}\" initialised", module_name.c_str());
        }
        return logger;
    }
    void Logger::shutdown() {
        get_logger(literals::logger::LOG)->info("Shutting down logger");
        s_loggers.clear();
        s_sinks.clear();
        spdlog::shutdown();
    }
}
