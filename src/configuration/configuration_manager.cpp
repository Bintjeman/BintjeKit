/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_manager.cpp
 */
#include "bintjekit/configuration/configuration_manager.hpp"
#include "bintjekit/configuration/utils.hpp"
namespace bnjkit {
    namespace conf {
        ConfigurationManager::ConfigurationManager() {
            m_json_data = nlohmann::json::object();
            m_default_values = nlohmann::json::object();
        }
        bool ConfigurationManager::load_from_file(const std::filesystem::path &path) {
            m_json_data = from_file(path);
            if (m_json_data.empty()) {
                return false;
            }
            return true;
        }
        bool ConfigurationManager::save_to_file(const std::filesystem::path &path) const {
            return to_file(path, m_json_data);
        }
        bool ConfigurationManager::merge_with_file(const std::filesystem::path &path) {
            // Charge le fichier
            auto file_json = conf::from_file(path);
            if (file_json.is_null()) {
                return false;
            }
            merge_json(m_json_data, file_json);
            return true;
        }
        void ConfigurationManager::set_default_values(const nlohmann::json &default_values) {
            m_default_values = default_values;
            reset_to_defaults();
        }

        void ConfigurationManager::reset_to_defaults() {
            m_json_data = m_default_values;
        }

        ConfigurationNode ConfigurationManager::get_root() {
            return ConfigurationNode(m_json_data);
        }
    } // conf
} // bnjkit
