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

namespace bnjkit {
    namespace conf {
        /**
         * @brief Represents the configuration settings that can be loaded, merged,
         *        saved, and manipulated through JSON and file paths.
         *
         * This class provides an abstraction for managing configuration settings,
         * allowing interaction with JSON objects, storage in files, and string/stream
         * representation. The settings can also be initialized with default values and
         * modified dynamically.
         */
        class Settings : public Node {
        public:
            explicit Settings();
            ~Settings();
            void load_from_json(const nlohmann::json& json, bool merge_default = true);
            void save_to_file(const std::filesystem::path& path = {}) const;
            [[nodiscard]] std::string to_string() const;
            [[nodiscard]] std::stringstream to_stream() const;
            void set_path(const std::filesystem::path& path);
            void set_default_values(const nlohmann::json& default_values);

        private:
            std::filesystem::path m_path;
            std::shared_ptr<spdlog::logger> m_logger;
        };
        class X : public Settings {
        public:
        };
    } // conf
} // bnjkit
#endif // BNJKIT_CONFIGURATION_SETTINGS_HPP
