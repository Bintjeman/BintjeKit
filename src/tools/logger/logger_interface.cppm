/*!
 * @file logger_interface.cppm
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
export module bik.logger:interface;
namespace bik::utils::logger {
    export class Logger {
    public:
        // Configure un logger unique (singleton)
        static void init(const std::string &filePath = "logs/log.txt",
                         spdlog::level::level_enum logLevel = spdlog::level::info);

        // Getter pour récupérer le logger global
        static std::shared_ptr<spdlog::logger> &getLogger();

        // Méthode pour modifier dynamiquement le niveau de log
        static void setLogLevel(spdlog::level::level_enum logLevel);

    private:
        static std::shared_ptr<spdlog::logger> logger_;
    };
}
