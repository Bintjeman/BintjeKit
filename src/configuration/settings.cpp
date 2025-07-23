/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_manager.cpp
 */
#include "bintjekit/configuration/settings.hpp"
#include "bintjekit/configuration/utils.hpp"
#include "bintjekit/logger.hpp"

namespace bnjkit::conf {
    std::shared_ptr<Settings> Settings::create(const std::filesystem::path& path, const nlohmann::json& default_values,
                                               const std::filesystem::path& default_path) {
        auto settings = create(from_file(path), default_values, default_path);
        if (!default_path.empty()) {
            settings->set_path(default_path);
        }else {
            settings->set_path(path);
        }
        return settings;
    }
    std::shared_ptr<Settings> Settings::create(const nlohmann::json& json, const nlohmann::json& default_values,
                                               const std::filesystem::path& default_path) {
        auto settings = std::make_shared<Settings>();
        settings->set_default_values(default_values);
        if (!default_path.empty()) {
            settings->set_path(default_path);
        }
        settings->load_from_json(json, true);
        return settings;
    }
    Settings::Settings() {
        m_logger->info("Constructor of Settings");
    }

    Settings::~Settings() = default;

    void Settings::load_from_json(const nlohmann::json& json, const bool merge_default) {
        m_logger->trace("Loading settings from json");
        if (json.empty()) {
            m_logger->warn("Le JSON reçu est vide");
        }
        m_logger->trace("JSON: {}", json.dump());
        * m_json = json;
        if (merge_default) {
            merge_with_json(* m_default_values);
        }
    }

    void Settings::save_to_file(const std::filesystem::path& path) const {
        m_logger->trace("Saving settings to file");
        std::filesystem::path p = path;
        if (path.empty()) {
            p = m_path;
        } else { p = path; }
        if (p.empty()) {
            m_logger->error("Empty save path");
            m_logger->warn("Use \"settings.json\"");
            p = "settings.json";
        }
        std::string str = m_json->dump();
        m_logger->trace("Saving settings to file: {}", p.string());
        m_logger->trace("Settings: {}", str);
        to_file(p, * m_json);
    }

    std::string Settings::to_string() const {
        return m_json->dump();
    }

    std::stringstream Settings::to_stream() const {
        return std::stringstream(m_json->dump());
    }
    std::filesystem::path Settings::path() const {
        return m_path;
    }
    std::string Settings::path_str() const {
        return m_path.string();
    }
    void Settings::set_path(const std::filesystem::path& path) {
        m_path = path;
    }

    void Settings::set_default_values(const nlohmann::json& default_values) const {
        * m_default_values = default_values;
    }
}
