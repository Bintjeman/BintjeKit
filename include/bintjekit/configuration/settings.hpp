/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_manager.hpp
 */
#ifndef BNJKIT_CONFIGURATION_SETTINGS_HPP
#define BNJKIT_CONFIGURATION_SETTINGS_HPP
#pragma once
#include <filesystem>
#include <sstream>
#include <nlohmann/json.hpp>
#include <spdlog/fwd.h>
#include "node.hpp"

namespace bnjkit::conf {
    /**
     * @brief Represents the configuration settings that can be loaded, merged,
     *        saved, and manipulated through JSON and file paths.
     *
     * This class provides an abstraction for managing configuration settings,
     * allowing interaction with JSON objects, storage in files, and stringstream
     * representation. The settings can also be initialized with default values and
     * modified dynamically.
     */
    class Settings final : public Node {
    public:
        static std::shared_ptr<Settings> create(const std::filesystem::path& path,
                                                const nlohmann::json& default_values = {},
                                                const std::filesystem::path& default_path = "");
        static std::shared_ptr<Settings> create(const nlohmann::json& json, const nlohmann::json& default_values = {},
                                                const std::filesystem::path& default_path = "");
        explicit Settings();
        ~Settings() override;
        /*!
         * Charge des nouvelles valeurs depuis un objet nlohmann::json
         *
         * @param json Les données
         * @param merge_default Si true: injecte les valeurs par default dans
         * les nouvelles données
         */
        void load_from_json(const nlohmann::json& json, bool merge_default = true);
        /*!
         * Sauve les données sous forme d'un json
         * @param path Le chemin du fichier de sortie
         */
        void save_to_file(const std::filesystem::path& path = {}) const;
        /*!
         * Converti en std::string les données
         * @return La chaîne de caractère générée
         */
        [[nodiscard]] std::string to_string() const;
        /*!
         * Converti en std::stringstream les données
         * @return Le stringstream généré
         */
        [[nodiscard]] std::stringstream to_stream() const;
        /*!
         * Retourne le chemin du fichier utilisé par default pour la sauvegarde
         * @return Le chemin du fichier
         */
        [[nodiscard]] std::filesystem::path path() const;
        /*!
         * Retourne le chemin du fichier utilisé par default pour la sauvegarde
         * @return Le chemin du fichier
         */
        [[nodiscard]] std::string path_str() const;

        /*!
         * Définit le chemin du fichier utilisé par default pour la sauvegarde
         * @param path Le chemin du fichier
         */
        void set_path(const std::filesystem::path& path);
        /*!
         * Définit les valeurs par default
         */
        void set_default_values(const nlohmann::json& default_values) const;

    private:
        std::filesystem::path m_path;
    };
}
#endif // BNJKIT_CONFIGURATION_SETTINGS_HPP
