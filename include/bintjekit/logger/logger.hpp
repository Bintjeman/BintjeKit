/*!
 * @author bintjeman
 * @date 14.06.25
 * @name logger.hpp
 */

#ifndef BNJKIT_CORE_LOGGER_HPP
#define BNJKIT_CORE_LOGGER_HPP
#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace bnjkit::core {
    class Logger {
    public:
        static void initialize();
        static void shutdown();
        static std::shared_ptr<spdlog::logger> get_logger(const std::string& module_name);
        static void set_module_level(const std::string& module_name,
                                     spdlog::level::level_enum level);

    private:
        static bool m_initialized;
        static std::vector<spdlog::sink_ptr> m_s_sinks;
        static std::unordered_map<std::string, std::shared_ptr<spdlog::logger> > m_s_loggers;
    };
}
#endif // BNJKIT_CORE_LOGGER_HPP
