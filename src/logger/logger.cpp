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
    bool Logger::m_initialized = false;
    std::vector<spdlog::sink_ptr> Logger::m_s_sinks;
    std::unordered_map<std::string, std::shared_ptr<spdlog::logger> > Logger::m_s_loggers;
    void Logger::initialize() {
        spdlog::enable_backtrace(32);
        const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("%^[%T] [%-8l] [%-8n] : %v%$");
        m_s_sinks.push_back(console_sink);
        const auto file_sink = std::make_shared<
            spdlog::sinks::basic_file_sink_mt>("bnjkit.log", true);
        file_sink->set_pattern("[%T] [%-8l] [%-8n] : %v");
        m_s_sinks.push_back(file_sink);
    }

    std::shared_ptr<spdlog::logger> Logger::get_logger(const std::string& module_name) {
        if (!m_initialized) {
            m_initialized = true;
            initialize();
        }
        if (const auto it = m_s_loggers.find(module_name); it != m_s_loggers.end()) {
            return it->second;
        }
        auto logger = std::make_shared<spdlog::logger>(module_name, m_s_sinks.begin(),
                                                       m_s_sinks.end());
        spdlog::register_logger(logger);
        logger->set_level(spdlog::level::info);
        m_s_loggers[module_name] = logger;
        if (module_name == module_names::LOG) {
            logger->info("Logger \"LOG\" initialised");
        } else {
            logger->warn("Logger \"{}\" initialised", module_name.c_str());
        }

        return logger;
    }

    void Logger::set_module_level(const std::string& module_name,
                                  const spdlog::level::level_enum level) {
        get_logger(module_name)->set_level(level);
    }

    void Logger::shutdown() {
        get_logger(module_names::LOG)->info("Shutting down logger");
        m_s_loggers.clear();
        m_s_sinks.clear();
        spdlog::shutdown();
    }
}
