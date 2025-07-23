/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_node.cpp
 */
#include "bintjekit/configuration/node.hpp"
#include "bintjekit/logger.hpp" // pour logger::logger::Logger::get_logger
#include "bintjekit/configuration/utils.hpp"

namespace bnjkit::conf {
    Node::Node(const std::shared_ptr<nlohmann::json>& json,
               const nlohmann::json::json_pointer& branch,
               const std::shared_ptr<nlohmann::json>& default_values
    ) {
        m_logger = logger::Logger::get_logger(literals::logger::CONFIGURATION);
        m_logger->trace("Constructor of Node");
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
        m_logger->trace("Branch: {}", branch.to_string());
        if (branch.empty()) {
            m_branch = ""_json_pointer;
        } else {
            m_branch = branch;
        }
        m_logger->trace("Constructor of Node finished");
        m_logger->trace("Node json: {}", m_json->dump());
        m_logger->trace("Node default json: {}", m_default_values->dump());
        m_logger->trace("Node branch: {}", m_branch.to_string());
        m_logger->trace("Nodes count: {}", node_count());
    }

    Node::~Node() = default;

    void Node::merge_with_json(const nlohmann::json& json) {
        m_logger->trace("Merging settings with json");
        merge_json(* m_json, json);
    }

    Node Node::create_child(const nlohmann::json::json_pointer& key) const {
        m_logger->trace("Creating child node");
        m_logger->trace("Nodes count: {}", node_count());
        const auto child_branch = m_branch / key;
        if (!m_json->contains(child_branch)) {
            (* m_json)[child_branch] = nlohmann::json::object();
        }
        m_logger->trace("Child branch: {}", child_branch.to_string());
        return Node(m_json, child_branch);
    }
    Node Node::create_child(const std::string& key) const {
        return create_child(nlohmann::json::json_pointer(key));
    }
    Node Node::root() const {
        return Node(m_json, nlohmann::json::json_pointer());
    }
    long Node::node_count() const {
        return m_json.use_count();
    }

    nlohmann::json::json_pointer Node::branch() {
        return m_branch;
    }
    std::string Node::branch_str() const {
        return m_branch.to_string();
    }
    nlohmann::json Node::get_json() const {
        return m_json->get<nlohmann::json>().at(m_branch);
    }

    void Node::reset_to_defaults() const {
        m_logger->trace("Resetting to defaults");
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
}
