/*!
 * @author bintjeman
 * @date 14.06.25
 * @name logger.hpp
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP
#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace bnjkit {
    namespace core {
        class Logger {
        public:
            static void initialize();
            static void shutdown();
            static std::shared_ptr<spdlog::logger> get_logger(const std::string &module_name);
            static void set_module_level(const std::string &module_name, spdlog::level::level_enum level);

        private:
            static std::vector<spdlog::sink_ptr> s_sinks;
            static std::unordered_map<std::string, std::shared_ptr<spdlog::logger> > s_loggers;
        };
    } // core
} // bnjkit
#define BNJKIT_LOG_TRACE(logger, ...)    logger->trace(__VA_ARGS__)
#define BNJKIT_LOG_INFO(logger, ...)     logger->info(__VA_ARGS__)
#define BNJKIT_LOG_WARN(logger, ...)     logger->warn(__VA_ARGS__)
#define BNJKIT_LOG_ERROR(logger, ...)    logger->error(__VA_ARGS__)
#define BNJKIT_LOG_CRITICAL(logger, ...) logger->critical(__VA_ARGS__)

#endif //LOGGER_HPP
