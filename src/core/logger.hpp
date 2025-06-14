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
            static std::shared_ptr<spdlog::logger> &get_core_logger();
            static std::shared_ptr<spdlog::logger> &get_app_logger();

        private:
            static std::shared_ptr<spdlog::logger> s_core_logger;
            static std::shared_ptr<spdlog::logger> s_app_logger;
        };
    } // core
} // bnjkit
#define BNJKIT_CORE_TRACE(...)    ::bnjkit::core::Logger::get_core_logger()->trace(__VA_ARGS__)
#define BNJKIT_CORE_INFO(...)     ::bnjkit::core::Logger::get_core_logger()->info(__VA_ARGS__)
#define BNJKIT_CORE_WARN(...)     ::bnjkit::core::Logger::get_core_logger()->warn(__VA_ARGS__)
#define BNJKIT_CORE_ERROR(...)    ::bnjkit::core::Logger::get_core_logger()->error(__VA_ARGS__)
#define BNJKIT_CORE_CRITICAL(...) ::bnjkit::core::Logger::get_core_logger()->critical(__VA_ARGS__)

#define BNJKIT_APP_TRACE(...)     ::bnjkit::core::Logger::get_app_logger()->trace(__VA_ARGS__)
#define BNJKIT_APP_INFO(...)      ::bnjkit::core::Logger::get_app_logger()->info(__VA_ARGS__)
#define BNJKIT_APP_WARN(...)      ::bnjkit::core::Logger::get_app_logger()->warn(__VA_ARGS__)
#define BNJKIT_APP_ERROR(...)     ::bnjkit::core::Logger::get_app_logger()->error(__VA_ARGS__)
#define BNJKIT_APP_CRITICAL(...)  ::bnjkit::core::Logger::get_app_logger()->critical(__VA_ARGS__)

#endif //LOGGER_HPP
