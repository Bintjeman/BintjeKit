/*!
 * @author bintjeman
 * @date 26.06.25
 * @name defaults_options.hpp
 */

#ifndef EVO_DEFAULTS_OPTIONS_HPP
#define EVO_DEFAULTS_OPTIONS_HPP
#pragma once
#include <map>
#include <spdlog/spdlog.h>

namespace evo {
    namespace app {
#ifdef NDEBUG
        // RELEASE OPTIONS
        constexpr auto DEFAULT_LOGGER_LEVEL = spdlog::level::warn;
        constexpr auto DEFAULT_CORE_LOGGER_LEVEL = spdlog::level::warn;
        constexpr auto DEFAULT_ENGINE_LOGGER_LEVEL = spdlog::level::warn;
        constexpr auto DEFAULT_CONF_LOGGER_LEVEL = spdlog::level::warn;
        constexpr auto DEFAULT_EVENT_LOGGER_LEVEL = spdlog::level::warn;
        constexpr auto DEFAULT_WINDOW_LOGGER_LEVEL = spdlog::level::warn;
        constexpr auto DEFAULT_RENDERER_LOGGER_LEVEL = spdlog::level::warn;
#else
        // DEBUG OPTIONS
        constexpr auto DEFAULT_LOGGER_LEVEL = spdlog::level::info;
        constexpr auto DEFAULT_CORE_LOGGER_LEVEL = spdlog::level::info;
        constexpr auto DEFAULT_ENGINE_LOGGER_LEVEL = spdlog::level::info;
        constexpr auto DEFAULT_CONF_LOGGER_LEVEL = spdlog::level::info;
        constexpr auto DEFAULT_EVENT_LOGGER_LEVEL = spdlog::level::info;
        constexpr auto DEFAULT_WINDOW_LOGGER_LEVEL = spdlog::level::info;
        constexpr auto DEFAULT_RENDERER_LOGGER_LEVEL = spdlog::level::info;
        constexpr auto DEFAULT_ENTITY_LOGGER_LEVEL = spdlog::level::trace;
#endif
        namespace opt {
            enum EnumOptions {
                CLION = 1 << 0,
                WORKDIR = 1 << 1,
                DEBUG = 1 << 2,
            };
            struct Option {
            public:
                Option(
                    char short_name,
                    std::string_view long_name,
                    std::string_view description,
                    EnumOptions options, bool value_requiered = false,
                    std::string_view default_value = "");
                std::string value{};
                bool forced{false};
                const char short_name;
                const std::string_view long_name;
                const std::string_view description;
                const EnumOptions options;
                const bool value_requiered{false};
                const std::string_view default_value{};
                void set_value(const std::string& value_str);
                static void make_options();
                static void add_option(const Option& option);
                static bool is_valide_option(const std::string& arg);
                static bool is_short(const std::string& arg);
                static bool is_long(const std::string& arg);
                static bool has_value(const std::string& arg);
                static Option& get_option(const std::string& arg);
                static Option& get_option(char arg);
                static Option& get_option(const EnumOptions& arg);
                static Option& parse_arg(const std::string& arg);
                static std::string get_value(const std::string& arg);
                static std::map<EnumOptions, Option> register_options;
                static std::map<char, EnumOptions> register_options_short;
                static std::map<std::string_view, EnumOptions> register_options_long;
                static std::vector<EnumOptions> effectives_options;
            };
            EnumOptions operator|(EnumOptions a, EnumOptions b);
            EnumOptions operator|=(EnumOptions& a, EnumOptions b);
            bool operator&(EnumOptions a, EnumOptions b);
        } // opt
    } // app
} // evo
#endif //EVO_DEFAULTS_OPTIONS_HPP
