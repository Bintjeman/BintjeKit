/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_node.cpp
 */
#include "bintjekit/configuration/node.hpp"

namespace bnjkit {
    namespace conf {
        Node::Node(const std::shared_ptr<nlohmann::json>& json,
                   const nlohmann::json::json_pointer& root,
                   const std::shared_ptr<nlohmann::json>& default_values) {
            if (json == nullptr) {
                m_json = std::make_shared<nlohmann::json>();
                * m_json = nlohmann::json::parse("{}");
            } else {
                m_json = json;
            }
            if (default_values == nullptr) {
                m_default_values = std::make_shared<nlohmann::json>();
                * m_default_values = nlohmann::json::parse("{}");
            } else {
                m_default_values = default_values;
            }
            if (m_branch.empty()) {
                m_branch = ""_json_pointer;
            } else {
                m_branch = root;
            }
        }
        Node Node::create_child(const nlohmann::json::json_pointer& key) {
            auto child_root = m_branch / key;
            if (!m_json->contains(child_root)) {
                (* m_json)[child_root] = nlohmann::json::object();
            }
            return Node(m_json, child_root);
        }
        nlohmann::json Node::get_json() const {
            return m_json->get<nlohmann::json>().at(m_branch);
        }
        void Node::reset_to_defaults() {
            if (!m_default_values) {
                throw std::runtime_error("Default values not initialized");
            }
            try {
                auto& target = m_json->at(m_branch);
                const auto& defaults = m_default_values->at(m_branch);
                target = defaults;
            } catch (const nlohmann::json::exception& e) {
                throw std::runtime_error("Failed to reset to defaults: " + std::string(e.what()));
            }
        }
    } // conf
} // bnjkit
