/*!
 * @author bintjeman
 * @date 15.06.25
 * @name utils.cpp
 */
#include "bintjekit/configuration/utils.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"

namespace bnjkit::conf {
    nlohmann::json from_file(const std::filesystem::path& path) {
        get_logger()->trace("Loading json from file");
        get_logger()->trace("path: {}", path.string());
        try {
            if (!std::filesystem::exists(path)) {
                get_logger()->warn("Le fichier de configuration n'existe pas: {}",
                                   path.string());
                return nlohmann::json::object();
            }

            std::ifstream file(path);
            if (!file.is_open()) {
                get_logger()->error("Impossible d'ouvrir le fichier: {}", path.string());
                return nlohmann::json::object();
            }

            std::string content((std::istreambuf_iterator(file)),
                                std::istreambuf_iterator<char>());

            if (content.empty()) {
                get_logger()->warn("Le fichier est vide: {}", path.string());
                return nlohmann::json::object();
            }

            get_logger()->trace("Raw content: {}", content);

            // Utilisation du parser avec des options de vérification strictes
            auto json = nlohmann::json::parse(content,
                                              nullptr, // callback pour erreurs
                                              true, // allow_exceptions
                                              true); // ignore_comments

            // Vérification supplémentaire de la structure
            if (!json.is_object()) {
                get_logger()->error("Le contenu n'est pas un objet JSON valide");
                return nlohmann::json::object();
            }

            get_logger()->trace("Parsed JSON: {}", json.dump(2));
            return json;
        } catch (const nlohmann::json::parse_error& e) {
            get_logger()->error("Erreur de parsing JSON dans {} à la position {}: {}",
                                path.string(), e.byte, e.what());
            return nlohmann::json::object();
        } catch (const std::exception& e) {
            get_logger()->error("Erreur lors de la lecture du fichier {}: {}",
                                path.string(), e.what());
            return nlohmann::json::object();
        }
    }
    nlohmann::json from_string(const std::string& str) {
        try {
            get_logger()->trace("Parsing JSON from string_view: {}", str);
            // Assurez-vous que le string_view est valide et non vide
            if (str.empty()) {
                get_logger()->warn("Empty string_view provided");
                return nlohmann::json::object();
            }

            // Construction d'une string temporaire à partir du string_view
            std::string temp_str(str.begin(), str.end());

            // Parse le JSON en vérifiant sa validité
            auto parsed = nlohmann::json::parse(temp_str, nullptr, true, true);
            get_logger()->trace("Parsed JSON: {}", parsed.dump(2));
            return parsed;
        } catch (const nlohmann::json::parse_error& e) {
            get_logger()->error("JSON parse error: {}", e.what());
            return nlohmann::json::object();
        }
    }
    nlohmann::json from_string(const std::string_view& str) {
        try {
            get_logger()->trace("Parsing JSON from string_view: {}", str);
            // Assurez-vous que le string_view est valide et non vide
            if (str.empty()) {
                get_logger()->warn("Empty string_view provided");
                return nlohmann::json::object();
            }

            // Construction d'une string temporaire à partir du string_view
            std::string temp_str(str.begin(), str.end());

            // Parse le JSON en vérifiant sa validité
            auto parsed = nlohmann::json::parse(temp_str, nullptr, true, true);
            get_logger()->trace("Parsed JSON: {}", parsed.dump(2));
            return parsed;
        } catch (const nlohmann::json::parse_error& e) {
            get_logger()->error("JSON parse error: {}", e.what());
            return nlohmann::json::object();
        }
    }
    bool to_file(const std::filesystem::path& path, const nlohmann::json& json) {
        get_logger()->trace("Saving json to file");
        get_logger()->trace("path: {}", path.string());
        get_logger()->trace("json: {}", json.dump());
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
        get_logger()->trace("Merging json");
        get_logger()->trace("target: {}", target.dump());
        get_logger()->trace("source: {}", source.dump());
        if (target.is_null()) {
            target = source;
            get_logger()->debug("Target was null, using source directly");
            return;
        }
        nlohmann::json tmp_json = source;
        tmp_json.merge_patch(target);
        target = tmp_json;
        get_logger()->trace("target result: {}", target.dump());
    }
    std::shared_ptr<spdlog::logger>& get_logger() {
        static auto logger = core::Logger::get_logger(core::module_names::CONFIGURATION);
        return logger;
    }
}
