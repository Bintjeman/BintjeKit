/*!
 * @author bintjeman
 * @date 03.07.25
 * @name defaults_options.cpp
 */
#include "defaults_options.hpp"

namespace evo::app::opt {
    std::map<EnumOptions, Option> Option::register_options;
    std::map<char, EnumOptions> Option::register_options_short;
    std::map<std::string_view, EnumOptions> Option::register_options_long;
    std::vector<EnumOptions> Option::effectives_options;
    Option::Option(char shortname, std::string_view longname,
                   std::string_view desc, EnumOptions opt, bool valuerequiered,
                   std::string_view defaultvalue)
        : short_name(shortname),
          long_name(longname),
          description(desc),
          options(opt),
          value_requiered(valuerequiered),
          default_value(defaultvalue) {
    }
    void Option::set_value(const std::string& value_str) {
        if (!forced) {
            value = value_str;
        }
    }
    void Option::make_options() {
        add_option({'d', "debug", "Debug mode", DEBUG});
        add_option({'c', "clion", "From clion", CLION});
        add_option({'w', "workdir", "Choose workdir", WORKDIR});
    }
    void Option::add_option(const Option& option) {
        register_options.insert({option.options, option});
        register_options_short.insert({option.short_name, option.options});
        register_options_long.insert({option.long_name, option.options});
    }
    bool Option::is_valide_option(const std::string& arg) {
        return is_short(arg) || is_long(arg);
    }
    bool Option::is_short(const std::string& arg) {
        return !arg.empty() && arg[0] == '-' && arg[1] != '-';
    }
    bool Option::is_long(const std::string& arg) {
        return !arg.empty() && arg.size() > 1 && arg[0] == '-' && arg[1] == '-';
    }
    bool Option::has_value(const std::string& arg) {
        return (arg.contains('=') && !arg.substr(arg.find('=') + 1).empty());
    }
    Option& Option::get_option(const std::string& arg) {
        if (is_valide_option(arg)) {
            if (is_long(arg)) {
                std::string long_name_tmp = arg.substr(2);
                std::string long_name;
                if (has_value(arg)) {
                    long_name = long_name_tmp.substr(0, long_name_tmp.find('='));
                } else {
                    long_name = long_name_tmp;
                }
                return register_options.at(register_options_long.at(long_name));
            }
            char short_name_tmp = arg[1];
            std::string short_name;
            if (has_value(arg)) {
                short_name = std::string(1, short_name_tmp) + arg.substr(arg.find('=') + 1);
            } else {
                short_name = std::string(1, short_name_tmp);
            }
            return register_options.at(register_options_short.at(short_name[0]));
        }
        throw std::runtime_error("Option " + std::string(arg) + " is not valid");
    }
    Option& Option::get_option(char arg) {
        return get_option(std::string(1, arg));
    }
    Option& Option::get_option(const EnumOptions& arg) {
        return register_options.at(arg);
    }
    Option& Option::parse_arg(const std::string& arg) {
        auto& option = get_option(arg);
        if (has_value(arg)) {
            option.set_value(get_value(arg));
        } else {
            if (option.value_requiered) {
                throw std::runtime_error("Option " + std::string(arg) + " require a value");
            }
        }
        effectives_options.push_back(option.options);
        return option;
    }
    std::string Option::get_value(const std::string& arg) {
        return arg.substr(arg.find('=') + 1);
    }
    EnumOptions operator|(const EnumOptions a, const EnumOptions b) {
        return static_cast<EnumOptions>(static_cast<int>(a) | static_cast<int>(b));
    }
    EnumOptions operator|=(EnumOptions& a, EnumOptions b) {
        return a = a | b;
    }
    bool operator&(const EnumOptions a, const EnumOptions b) {
        return static_cast<bool>(static_cast<int>(a) & static_cast<int>(b));
    }
}
