/*!
 * @author bintjeman
 * @date 15.06.25
 * @name util.hpp
 */

#ifndef UTIL_HPP
#define UTIL_HPP
#pragma once
#include <filesystem>
#include <nlohmann/json_fwd.hpp>
namespace bnjkit {
    namespace conf {
        nlohmann::json from_file(const std::filesystem::path &path);
        nlohmann::json from_string(const std::string &str);
        nlohmann::json from_string(const std::string_view &str);
        bool to_file(const std::filesystem::path &path, const nlohmann::json &json);
        void merge_json(nlohmann::json& target, const nlohmann::json& source);
    }
}
#endif //UTIL_HPP
