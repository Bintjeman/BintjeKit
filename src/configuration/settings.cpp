/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_manager.cpp
 */
#include "bintjekit/configuration/settings.hpp"
#include "bintjekit/configuration/utils.hpp"

namespace bnjkit {
    namespace conf {
        Settings::Settings(): Node() {
        }
        Settings::~Settings() = default;
        void Settings::load_from_json(const nlohmann::json& json) {
            * m_json = json;
            m_default_values = std::make_shared<nlohmann::json>();
        }
        void Settings::merge_with_json(const nlohmann::json& json) {
            merge_json(* m_json, json);
        }
        void Settings::save_to_file(const std::filesystem::path& path) const {
            std::filesystem::path p = path;
            if (path.empty()) {
                p = m_path;
            } else { p = path; }
            to_file(p, * m_json);
        }
        std::string Settings::to_string() const {
            return m_json->dump();
        }
        std::stringstream Settings::to_stream() const {
            return std::stringstream(m_json->dump());
        }
        void Settings::set_path(const std::filesystem::path& path) {
            m_path = path;
        }
        void Settings::set_default_values(const nlohmann::json& default_values) {
            * m_default_values = default_values;
        }
    } // conf
} // bnjkit
