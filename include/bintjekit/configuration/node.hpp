/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_node.hpp
 */

#ifndef BNJKIT_CONFIGURATION_NODE_HPP
#define BNJKIT_CONFIGURATION_NODE_HPP
#pragma once
#include <nlohmann/json.hpp>
#include "spdlog/fwd.h"

namespace bnjkit::conf {
        /*!
         * @class Node
         * @brief A class representing a single node in a nlohmann JSON data structure.
         *
         */
    class Node {
    public:
        explicit Node(const std::shared_ptr<nlohmann::json>& json = nullptr,
                      const nlohmann::json::json_pointer& branch = ""_json_pointer,
                      const std::shared_ptr<nlohmann::json>& default_values = nullptr);
        virtual ~Node();
        /*!
         * Injecte les données de json dans les données existantes. Les données\
         * existante ne sont jamais modifiées. Les données inéxistante dans l'\
         * origine et présente dans le json sont ajoutées.
         *
         * @param json Les donnée json à merger avec les données existante du node
         */
        void merge_with_json(const nlohmann::json& json);
        template<typename T>
        T get(const nlohmann::json::json_pointer& key, const T& default_value) const;
        template<typename T>
        T get(const nlohmann::json::json_pointer& key) const;
        template<typename T>
        T get_or_set(const nlohmann::json::json_pointer& key, const T& default_value);
        template<typename T>
        void set(const nlohmann::json::json_pointer& key, const T& value);
        template<typename T>
        T get(const std::string& key, const T& default_value) const;
        template<typename T>
        T get(const std::string& key) const;
        template<typename T>
        T get_or_set(const std::string& key, const T& default_value);
        template<typename T>
        void set(const std::string& key, const T& value);
        /*!
         * @return Le pointeur sur la branche courante du node
         */
        [[nodiscard]] nlohmann::json::json_pointer branch();
        /*!
         * @return Le pointeur sur la branche courante du node
         */
        [[nodiscard]] std::string branch_str() const;
        /*!
         * @return Les données json
         */
        [[nodiscard]] nlohmann::json get_json() const;
        /*!
         * Réinitialise toutes les valeurs des données aux valeurs par defaults.
         *
         * @todo Mettre en place un meilleurs système de gestion des valeurs
         * par default
         */
        void reset_to_defaults() const;
        /*!
         * @return Le pointeur sur la branche courante du node
         */
        [[nodiscard]] std::shared_ptr<spdlog::logger>& logger();
        /*!
         * @return Le pointeur sur la branche courante du node
         */
        [[nodiscard]] std::shared_ptr<spdlog::logger> const& logger() const;
        /*!
         * Retourne un node fille de this. Les données sont identiques et
         * partagées
         *
         * @param key Le chemin vers la base de la nouvelle branche fille
         * @return Un node fille avec les mêmes données
         */
        [[nodiscard]] Node create_child(const nlohmann::json::json_pointer& key) const;
        /*!
         *
         * @return Le nombre de node partageant les données
         */
        [[nodiscard]] long node_count() const;

    protected:
        std::shared_ptr<spdlog::logger> m_logger; //< Le logger "CONFIGURATION"
        std::shared_ptr<nlohmann::json> m_json; //< Les données json
        std::shared_ptr<nlohmann::json> m_default_values; //< Les valeurs par default
        nlohmann::json::json_pointer m_branch; //< Le pointeur sur la branche
    };
}
#include "node.inl"
#endif // BNJKIT_CONFIGURATION_NODE_HPP
