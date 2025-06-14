/*!
 * @author bintjeman
 * @date 14.06.25
 * @name logger.cpp
 */

#include "logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
namespace bnjkit {
    namespace core {
        std::shared_ptr<spdlog::logger> Logger::s_core_logger;
        std::shared_ptr<spdlog::logger> Logger::s_app_logger;
        void Logger::initialize() {
            std::vector<spdlog::sink_ptr> log_sinks;
            // Console sink avec couleurs
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_pattern("%^[%T] %n: %v%$");
            log_sinks.push_back(console_sink);
            // File sink
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("bnjkit.log", true);
            file_sink->set_pattern("[%T] [%l] %n: %v");
            log_sinks.push_back(file_sink);
            // Créer les loggers
            s_core_logger = std::make_shared<spdlog::logger>("BNJKIT", begin(log_sinks), end(log_sinks));
            spdlog::register_logger(s_core_logger);
            s_core_logger->set_level(spdlog::level::trace);
            s_core_logger->flush_on(spdlog::level::trace);
            s_app_logger = std::make_shared<spdlog::logger>("APP", begin(log_sinks), end(log_sinks));
            spdlog::register_logger(s_app_logger);
            s_app_logger->set_level(spdlog::level::trace);
            s_app_logger->flush_on(spdlog::level::trace);
        }
        void Logger::shutdown() {
            s_app_logger.reset();
            s_core_logger.reset();
            spdlog::shutdown();
        }
        std::shared_ptr<spdlog::logger> &Logger::get_core_logger() {
            return s_core_logger;
        }
        std::shared_ptr<spdlog::logger> &Logger::get_app_logger() {
            return s_app_logger;
        }
    } // core
} // bnjkit
