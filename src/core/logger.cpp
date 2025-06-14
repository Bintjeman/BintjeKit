/*!
 * @author bintjeman
 * @date 14.06.25
 * @name logger.cpp
 */

#include "../../include/bintjekit/core/logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "bintjekit/core/common.hpp"

namespace bnjkit {
    namespace core {
        std::vector<spdlog::sink_ptr> Logger::s_sinks;
        std::unordered_map<std::string, std::shared_ptr<spdlog::logger> > Logger::s_loggers;

        void Logger::initialize() {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_pattern("%^[%T] [%l] %n: %v%$");
            s_sinks.push_back(console_sink);
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("bnjkit.log", true);
            file_sink->set_pattern("[%T] [%l] %n: %v");
            s_sinks.push_back(file_sink);
            // Créer les loggers par défaut
            get_logger(module_names::LOG)->set_level(spdlog::level::trace);
            get_logger(module_names::CORE)->set_level(spdlog::level::trace);
            get_logger(module_names::APP)->set_level(spdlog::level::info);
        }

        std::shared_ptr<spdlog::logger> Logger::get_logger(const std::string &module_name) {
            auto it = s_loggers.find(module_name);
            if (it != s_loggers.end()) {
                return it->second;
            }
            auto logger = std::make_shared<spdlog::logger>(module_name, s_sinks.begin(), s_sinks.end());
            spdlog::register_logger(logger);
            logger->set_level(spdlog::level::info);
            logger->flush_on(spdlog::level::trace);
            s_loggers[module_name] = logger;
            if (module_name == module_names::LOG) {
                logger->info("Logger \"LOG\" initialised");
            }else {
                logger->warn("Logger \"{}\" initialised", module_name.c_str());
            }
            return logger;
        }

        void Logger::set_module_level(const std::string &module_name, spdlog::level::level_enum level) {
            get_logger(module_name)->set_level(level);
        }

        void Logger::shutdown() {
            s_loggers.clear();
            s_sinks.clear();
            spdlog::shutdown();
        }
    } // core
} // bnjkit
