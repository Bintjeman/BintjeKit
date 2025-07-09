/*!
 * @author bintjeman
 * @date 15.06.25
 * @name util.hpp
 */

#ifndef BNJKIT_CONFIGURATION_UTIL_HPP
#define BNJKIT_CONFIGURATION_UTIL_HPP
#pragma once
#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <spdlog/fwd.h>

namespace bnjkit::conf {
    nlohmann::json from_file(const std::filesystem::path &path);
    nlohmann::json from_string(const std::string &str);
    nlohmann::json from_string(const std::string_view &str);
    bool to_file(const std::filesystem::path &path, const nlohmann::json &json);
    void merge_json(nlohmann::json& target, const nlohmann::json& source);
    std::shared_ptr<spdlog::logger>& get_logger();
}
#endif // BNJKIT_CONFIGURATION_UTIL_HPP
