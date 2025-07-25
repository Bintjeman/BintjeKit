/*!
 * @author bintjeman
 * @date 23.07.25
 * @name common.hpp
 */

#ifndef COMMON_HPP
#define COMMON_HPP
#pragma once
#include <string>
#include <filesystem>

namespace evo::common {
    struct Literals {
        const char* app_name = "Evobot";
        const char* default_settings_path = "evobot.json";
        const char* default_log_file_name = "log.log";
    };
    inline constexpr Literals literals;
    struct SettingsChild {
        const char* logger = "/Logger";
        const char* evobot = "/Evobot";
    };
    inline constexpr SettingsChild settings_child;
    struct Data {
        std::string application_name = literals.app_name;
        std::filesystem::path application_path{};
        std::filesystem::path settings_path{literals.default_settings_path};
    };
    extern Data data;
}
#endif
