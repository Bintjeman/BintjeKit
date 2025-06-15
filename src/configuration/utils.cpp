/*!
 * @author bintjeman
 * @date 15.06.25
 * @name utils.cpp
 */
#include "bintjekit/configuration/utils.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace bnjkit {
    namespace conf {
        nlohmann::json from_file(const std::filesystem::path &path) {
            try {
                if (!std::filesystem::exists(path)) {
                    return {};
                }
                std::ifstream file(path);
                if (!file.is_open()) {
                    return {};
                }
                return nlohmann::json::parse(file);
            } catch (const nlohmann::json::parse_error &e[[maybe_unused]]) {
                // En cas d'erreur de parsing, on garde les données actuelles
                return {};
            } catch (const std::exception &e[[maybe_unused]]) {
                // Autres erreurs possibles (permissions, etc.)
                return {};
            }
        }

        bool to_file(const std::filesystem::path &path, const nlohmann::json &json) {
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
            } catch (const std::filesystem::filesystem_error &e[[maybe_unused]]) {
                // Erreur lors de la création des répertoires
                return false;
            } catch (const std::exception &e[[maybe_unused]]) {
                // Autres erreurs possibles (permissions, etc.)
                return false;
            }
        }

        void merge_json(nlohmann::json &target, const nlohmann::json &source) {
            if (!source.is_object()) {
                target = source;
                return;
            }
            for (const auto &[key, value]: source.items()) {
                if (value.is_object() && target.contains(key) && target[key].is_object()) {
                    merge_json(target[key], value);
                } else {
                    target[key] = value;
                }
            }
        }
    } // conf
} // bnjkit
