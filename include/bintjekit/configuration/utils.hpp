/*!
 * @author bintjeman
 * @date 15.06.25
 * @name util.hpp
 *
 * Collection d'utilitaires pour aider à la manipulation d'objet nlohmann::json
 */

#ifndef BNJKIT_CONFIGURATION_UTIL_HPP
#define BNJKIT_CONFIGURATION_UTIL_HPP
#pragma once
#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <spdlog/fwd.h>

namespace bnjkit::conf {
    nlohmann::json from_file(const std::filesystem::path& path);
    nlohmann::json from_string(const std::string& str);
    nlohmann::json from_string(const std::string_view& str);
    bool to_file(const std::filesystem::path& path, const nlohmann::json& json);
    /*!
     * Fusionne deux arbres de données de nlohmann::json. La cible a la priorité sur la source
     *
     * @param target Les données dans lesquelles on insère la source
     * @param source Les données à insérer dans la cible
     */
    void merge_json(nlohmann::json& target, const nlohmann::json& source);
    std::shared_ptr<spdlog::logger>& get_logger();
}
#endif // BNJKIT_CONFIGURATION_UTIL_HPP
