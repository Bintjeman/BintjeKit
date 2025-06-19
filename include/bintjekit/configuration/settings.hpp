/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_manager.hpp
 */
#ifndef CONFIGURATION_MANAGER_HPP
#define CONFIGURATION_MANAGER_HPP
#pragma once
#include <filesystem>
#include <sstream>
#include <nlohmann/json.hpp>
#include "node.hpp"

namespace bnjkit {
    namespace conf {
        class Settings : public Node {
        public:
            explicit Settings(const std::shared_ptr<nlohmann::json>& json = nullptr,
                     const nlohmann::json::json_pointer& root = ""_json_pointer);
            ~Settings();

            void load_from_file(const std::filesystem::path& path);
            void load_from_string(const std::string& json_string);
            void load_from_json(const nlohmann::json& json);
            void merge_with_file(const std::filesystem::path& path={});
            void save_to_file(const std::filesystem::path& path={}) const;
            [[nodiscard]] std::string to_string() const;
            [[nodiscard]] std::stringstream to_stream() const;
            void set_path(const std::filesystem::path& path);
            void set_default_values(const nlohmann::json& default_values);
        private:
            std::filesystem::path m_path;
        };
    } // conf
} // bnjkit
#endif //CONFIGURATION_MANAGER_HPP
