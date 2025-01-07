/*!
 * @file settings_manager_impl.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <fstream>
#include <filesystem>
// #include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <nlohmann/detail/json_pointer.hpp>
#include "tools/logger/logger_define.hpp"
export module settings:impl;
import :interface;
import logger;
namespace bik::config {
    Settings::Settings() {
        json_ = std::make_shared<nlohmann::json>();
        *json_ = nlohmann::json::parse("{}");
    }

    void Settings::load(const std::filesystem::path &filepath) {
        LOGGER->info("Settings::load()");
        std::ifstream file(filepath);
        if (!file.is_open()) {
            LOGGER->error("Impossible d'ouvrir le fichier JSON : {}", filepath.string());
            throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + filepath.string());
        }
        file >> *json_;
    }

    void Settings::save(const std::filesystem::path &filepath) const {
        LOGGER->info("Settings::save()");
        std::ofstream file(filepath);
        if (!file.is_open()) {
            LOGGER->error("Impossible d'ouvrir le fichier JSON : {}", filepath.string());
            throw std::runtime_error("Impossible d'écrire dans le fichier JSON : " + filepath.string());
        }
        file << json_->dump(4);
    }
} // namespace bik::config
