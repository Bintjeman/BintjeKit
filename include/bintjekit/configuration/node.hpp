/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_node.hpp
 */

#ifndef BNJKIT_CONFIGURATION_NODE_HPP
#define BNJKIT_CONFIGURATION_NODE_HPP
#pragma once
#include <nlohmann/json.hpp>
#include "spdlog/fwd.h"

namespace bnjkit {
    namespace conf {
        /**
         * @class Node
         * @brief A class representing a single node in a nlohmann json data structure.
         *
         */
        class Node {
        public:
            explicit Node(const std::shared_ptr<nlohmann::json>& json = nullptr,
                          const nlohmann::json::json_pointer& branch = ""_json_pointer,
                          const std::shared_ptr<nlohmann::json>& default_values = nullptr);
            virtual ~Node();
            void merge_with_json(const nlohmann::json& json);
            template<typename T>
            T get(const nlohmann::json::json_pointer& key, const T& defaultValue) const;
            template<typename T>
            T get(const nlohmann::json::json_pointer& key) const;
            template<typename T>
            T get_or_set(const nlohmann::json::json_pointer& key, const T& defaultValue);
            template<typename T>
            void set(const nlohmann::json::json_pointer& key, const T& value);
            [[nodiscard]] nlohmann::json::json_pointer branch();
            [[nodiscard]] std::string branch_str() const;
            [[nodiscard]] nlohmann::json get_json() const;
            void reset_to_defaults();
            Node create_child(const nlohmann::json::json_pointer& key);
            unsigned int node_count() const;
        protected:
            std::shared_ptr<spdlog::logger> m_logger;
            std::shared_ptr<nlohmann::json> m_json;
            std::shared_ptr<nlohmann::json> m_default_values;
            nlohmann::json::json_pointer m_branch;
        };
    } // conf
} // bnjkit
#include "node.inl"
#endif // BNJKIT_CONFIGURATION_NODE_HPP
