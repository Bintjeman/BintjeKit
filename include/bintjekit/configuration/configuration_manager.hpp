/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_manager.hpp
 */
#ifndef CONFIGURATION_MANAGER_HPP
#define CONFIGURATION_MANAGER_HPP
#pragma once
#include <filesystem>
#include <nlohmann/json.hpp>
#include "configuration_node.hpp"
namespace bnjkit {
    namespace conf {
        class ConfigurationManager {
        public:
            ConfigurationManager();
            bool load_from_file(const std::filesystem::path &path);
            bool save_to_file(const std::filesystem::path &path) const;
            bool merge_with_file(const std::filesystem::path &path);
            void set_default_values(const nlohmann::json &default_values);
            void reset_to_defaults();
            ConfigurationNode get_root();
            // Méthodes utilitaires pour accéder directement aux valeurs
            template<typename T>
            T get(const std::string &key, const T &default_value = T{}) {
                return get_root().get<T>(key, default_value);
            }
            template<typename T>
            void set(const std::string &key, const T &value) {
                get_root().set(key, value);
            }
        private:
            nlohmann::json m_json_data;
            nlohmann::json m_default_values;
        };
    } // conf
} // bnjkit
#endif //CONFIGURATION_MANAGER_HPP
