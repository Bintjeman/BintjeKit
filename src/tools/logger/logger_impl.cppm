/*!
 * @file logger_impl.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
// #include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
export module logger:impl;
import :interface;
namespace bik::utils::logger {
    std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;

    void Logger::init(const std::string &filePath, spdlog::level::level_enum logLevel) {
        logger_ = spdlog::basic_logger_mt("logger", filePath, true);
        logger_->set_level(logLevel);
    }

    std::shared_ptr<spdlog::logger> &Logger::getLogger() {
        if (!logger_) {
            throw std::runtime_error("Logger non initialisé. Appeler Logger::init() avant d'utiliser getLogger().");
        }
        return logger_;
    }

    void Logger::setLogLevel(spdlog::level::level_enum logLevel) {
        if (logger_) {
            logger_->set_level(logLevel);
        }
    }
} // namespace bik::utils
