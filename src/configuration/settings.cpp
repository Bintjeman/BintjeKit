/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_manager.cpp
 */
#include "bintjekit/configuration/settings.hpp"
#include "bintjekit/configuration/utils.hpp"
#include "bintjekit/logger.hpp"
namespace bnjkit {
    namespace conf {
        Settings::Settings(): Node() {
            m_logger = core::Logger::get_logger(core::module_names::CONFIGURATION);
            m_logger->set_level(spdlog::level::trace);
            m_logger->info("Constructor of Settings");
        }
        Settings::~Settings() = default;
        void Settings::load_from_json(const nlohmann::json& json, bool merge_default) {
            m_logger->info("Loading settings from json");
            if (json.empty()) {
                m_logger->warn("Le JSON reçu est vide");
            }
            m_logger->trace("JSON: {}", json.dump());
            *m_json = json;
            if (merge_default) {
                merge_with_json(*m_default_values);
            }
        }
        void Settings::merge_with_json(const nlohmann::json& json) {
            m_logger->info("Merging settings with json");
            merge_json(* m_json, json);
        }
        void Settings::save_to_file(const std::filesystem::path& path) const {
            m_logger->info("Saving settings to file");
            std::filesystem::path p = path;
            if (path.empty()) {
                p = m_path;
            } else { p = path; }
            std::string str = m_json->dump();
            m_logger->info("Saving settings to file: {}", p.string());
            m_logger->trace("Settings: {}", str);
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
