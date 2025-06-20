/*!
 * @author bintjeman
 * @date 15.06.25
 * @name utils.cpp
 */
#include "bintjekit/configuration/utils.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include "bintjekit/core/common.hpp""
#include "bintjekit/core/logger.hpp"

namespace bnjkit {
    namespace conf {
        nlohmann::json from_file(const std::filesystem::path& path) {
            std::shared_ptr<spdlog::logger> logger = core::Logger::get_logger(core::module_names::CONFIGURATION);
            try {
                if (!std::filesystem::exists(path)) {
                    logger->warn("Le fichier de configuration n'existe pas: {}", path.string());
                    return {};
                }
                std::ifstream file(path);
                if (!file.is_open()) {
                    logger->error("Impossible d'ouvrir le fichier: {}", path.string());
                    return {};
                }

                std::string content((std::istreambuf_iterator<char>(file)),
                                   std::istreambuf_iterator<char>());
                if (content.empty()) {
                    logger->warn("Le fichier est vide: {}", path.string());
                    return {};
                }
                return nlohmann::json::parse(content);
            } catch (const nlohmann::json::parse_error& e) {
                logger->error("Erreur de parsing JSON dans {}: {}", path.string(), e.what());
                return {};
            } catch (const std::exception& e) {
                logger->error("Erreur lors de la lecture du fichier {}: {}", path.string(), e.what());
                return {};
            }

        }

        nlohmann::json from_string(const std::string& str) {
            return nlohmann::json::parse(str);
        }
        nlohmann::json from_string(const std::string_view& str) {
            return nlohmann::json::parse(str);
        }
        bool to_file(const std::filesystem::path& path, const nlohmann::json& json) {
            try {
                // Création des répertoires parents si nécessaire
                const auto parent_path = path.parent_path();
                if (!parent_path.empty()) {
                    std::filesystem::create_directories(parent_path);
                }
                // Ouverture du fichier en écriture
                std::ofstream file(path);
                if (!file.is_open()) {
                    return false;
                }
                // Écriture du JSON formaté avec indentation

                file << json.dump(4);
                return true;
            } catch (const std::filesystem::filesystem_error& e[[maybe_unused]]) {
                // Erreur lors de la création des répertoires
                return false;
            } catch (const std::exception& e[[maybe_unused]]) {
                // Autres erreurs possibles (permissions, etc.)
                return false;
            }
        }
        void merge_json(nlohmann::json& target, const nlohmann::json& source) {
            nlohmann::json tmp_json = source;
            tmp_json.merge_patch(target);
            target = tmp_json;
        }
    } // conf
} // bnjkit
