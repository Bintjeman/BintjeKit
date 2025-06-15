/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_node.hpp
 */

#ifndef CONFIGURATION_NODE_HPP
#define CONFIGURATION_NODE_HPP
#pragma once
#include <string>
#include <nlohmann/json.hpp>
namespace bnjkit {
    namespace conf {
        class ConfigurationNode {
        public:
            explicit ConfigurationNode(nlohmann::json &json_data, const std::string &branch = "");
            template<typename T>
            T get(const std::string &key, const T &default_value = T{}) const {
                try {
                    const auto full_key = get_full_key(key);
                    return json_.value(full_key, default_value);
                } catch (...) {
                    return default_value;
                }
            }
            template<typename T>
            void set(const std::string &key, const T &value) {
                const auto full_key = get_full_key(key);
                json_[full_key] = value;
            }
            template<typename T>
            T get_or_set(const std::string &key, const T &default_value = T{}) {
                const auto full_key = get_full_key(key);
                if (!json_.contains(full_key)) {
                    json_[full_key] = default_value;
                }
                return json_[full_key].get<T>();
            }
            ConfigurationNode get_child(const std::string &key) ;
        private:
            std::string get_full_key(const std::string &key) const;
            nlohmann::json &json_;
            std::string branch_;
        };
    } // conf
} // bnjkit

#endif //CONFIGURATION_NODE_HPP
