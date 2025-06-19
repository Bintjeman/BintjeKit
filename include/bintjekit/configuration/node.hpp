/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_node.hpp
 */

#ifndef CONFIGURATION_NODE_HPP
#define CONFIGURATION_NODE_HPP
#pragma once
#include <nlohmann/json.hpp>

namespace bnjkit {
    namespace conf {
        class Node {
        public:
            explicit Node(const std::shared_ptr<nlohmann::json>& json = nullptr,
                          const nlohmann::json::json_pointer& root = ""_json_pointer,const std::shared_ptr<nlohmann::json>& default_values = nullptr);
            template<typename T>
            T get(const nlohmann::json::json_pointer& key, const T& defaultValue) const;
            template<typename T>
            T get(const nlohmann::json::json_pointer& key) const;
            template<typename T>
            T get_or_set(const nlohmann::json::json_pointer& key, const T& defaultValue);
            template<typename T>
            void set(const nlohmann::json::json_pointer& key, const T& value);
            [[nodiscard]] nlohmann::json get_json() const;
            void reset_to_defaults();
            Node create_child(const nlohmann::json::json_pointer& key);

        protected:
            std::shared_ptr<nlohmann::json> m_json;
            std::shared_ptr<nlohmann::json> m_default_values;
            nlohmann::json::json_pointer m_branch;
        };
    } // conf
} // bnjkit
#include "node.inl"
#endif //CONFIGURATION_NODE_HPP
