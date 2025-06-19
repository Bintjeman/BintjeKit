/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_manager.cpp
 */
#include "bintjekit/configuration/settings.hpp"
#include "bintjekit/configuration/utils.hpp"

namespace bnjkit {
    namespace conf {
        Settings::Settings(const std::shared_ptr<nlohmann::json>& json[[maybe_unused]],
                           const nlohmann::json::json_pointer& root[[maybe_unused]]) {
            m_json = json;
            m_branch = root;
            m_path = "";
        }
        Settings::~Settings() = default;
        void Settings::load_from_file(const std::filesystem::path& path) {
            std::filesystem::path p = path;
            if (path.empty()) {
                p = m_path;
            } else { p = path; }
            * m_json = from_file(p);
        }
        void Settings::load_from_string(const std::string& json_string) {
            * m_json = nlohmann::json::parse(json_string);
        }
        void Settings::load_from_json(const nlohmann::json& json) {
            * m_json = json;
        }
        void Settings::merge_with_file(const std::filesystem::path& path) {
            merge_json(* m_json, from_file(path));
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
            * m_json = default_values;
        }
    } // conf
} // bnjkit
