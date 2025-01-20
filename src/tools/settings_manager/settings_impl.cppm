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
#include <nlohmann/detail/json_pointer.hpp>
#include <spdlog/spdlog.h>

#include "tools/logger/logger_define.hpp"
export module bik.settings:impl;
import :interface;
import bik.logger;
namespace bik::settings {
    Settings::Settings() {
        LOGGER->info("Settings::Settings()");
        json_ = std::make_shared<nlohmann::json>();
        *json_ = nlohmann::json::parse("{}");
    }

    void Settings::load(const std::filesystem::path &filepath, LoadMode mode) {
        LOGGER->info("Settings::load()");
        LOGGER->flush();
        std::ifstream file(filepath);
        if (!file.is_open()) {
            LOGGER->error("Impossible d'ouvrir le fichier JSON : {}", filepath.string());
            LOGGER->flush();
            switch (mode) {
                case LoadMode::CREATE: {
                    LOGGER->warn("Création du fichier JSON : {}", filepath.string());
                    std::ofstream new_file(filepath);
                    new_file << "{}";
                    new_file.close();
                    file.open(filepath);
                    break;
                }
                case LoadMode::NOTHING:
                    return;
                case LoadMode::ERROR:
                    throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + filepath.string());
                    break;
            }
        }
        file >> *json_;
        LOGGER->trace("Json:\n\"{}\"", json_->dump(4));
        file.close();
    }

    void Settings::save(const std::filesystem::path &filepath) const {
        LOGGER->info("Settings::save()");
        std::ofstream file(filepath);
        if (!file.is_open()) {
            LOGGER->error("Impossible d'ouvrir le fichier JSON : {}", filepath.string());
            throw std::runtime_error("Impossible d'écrire dans le fichier JSON : " + filepath.string());
        }
        LOGGER->trace("Json:\n\"{}\"", json_->dump(4));
        file << json_->dump(4);
    }
} // namespace bik::config
