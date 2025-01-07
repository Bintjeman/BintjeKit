/*!
 * @file node_impl.cppm
 * @author bintjeman
 * @date 06.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/detail/json_pointer.hpp>
#include <spdlog/spdlog.h>
#include "tools/logger/logger_define.hpp"
export module settings:node_impl;
import :node;

int Node::node_counter = 0;

Node::Node(const std::shared_ptr<nlohmann::json> &json, const nlohmann::json::json_pointer &root) {
    node_counter++;
    root_ = root;
    if (json == nullptr) {
        json_ = std::make_shared<nlohmann::json>();
        *json_ = nlohmann::json::parse("{}");
    } else {
        json_ = json;
    }
    LOGGER->trace("Node::Node(const std::shared_ptr<Json>& json, const nlohmann::json::json_pointer &root)");
    LOGGER->trace("json shared counter: {}", json_.use_count());
    LOGGER->trace("node counter: {}", node_counter);
    LOGGER->trace("root: \"{}\"", root_.to_string());
    LOGGER->trace("json: \"{}\"", json_->dump(4));
}

Node::~Node() {
    LOGGER->trace("Node::~Node()");
    node_counter--;
}

template<typename T>
T Node::get(const nlohmann::json::json_pointer &key, const T &defaultValue) const {
    auto ptr = root_ / key;
    LOGGER->trace("Node::get(const nlohmann::json::json_pointer &key, const T &defaultValue) const");
    LOGGER->trace("key \"{}\" / root \"{}\" = ptr: \"{}\"", key.to_string(), root_.to_string(), ptr.to_string());
    if (!json_->contains(ptr)) {
        return defaultValue;
    } else {
        return json_->at(ptr).get<T>();
    }
}

template<typename T>
T Node::get_or_set(const nlohmann::json::json_pointer &key, const T &defaultValue) {
    auto ptr = root_ / key;
    LOGGER->trace("Node::get_or_set(const nlohmann::json::json_pointer &key, const T &defaultValue)");
    LOGGER->trace("key \"{}\" / root \"{}\" = ptr: \"{}\"", key.to_string(), root_.to_string(), ptr.to_string());
    if (!json_->contains(ptr)) {
        set_inner(key, defaultValue);
        return defaultValue;
    } else {
        return json_->at(ptr).get<T>();
    }
}

template<typename T>
void Node::set(const nlohmann::json::json_pointer &key, const T &value) {
    LOGGER->trace("Node::set(const nlohmann::json::json_pointer &key, const T &value)");
    LOGGER->trace("key \"{}\" / root \"{}\"", key.to_string(), root_.to_string());
    LOGGER->trace("value: \"{}\"", value);
    set_inner(root_ / key, value);
}

Node Node::create_child(const nlohmann::json::json_pointer &key) {
    auto child_root = root_ / key;
    // Vérifier si le JSON contient le pointeur correspondant
    if (!json_->contains(child_root)) {
        // Si le chemin n'existe pas, créer un nœud JSON vide à cet emplacement
        (*json_)[child_root] = nlohmann::json::object();
    }
    return Node(json_, child_root);
}

template<typename T>
void Node::set_inner(const nlohmann::json::json_pointer &key, const T &value) {
    LOGGER->trace("Node::set_inner(const nlohmann::json::json_pointer &key, const T &value)");
    LOGGER->trace("key \"{}\" / root \"{}\"", key.to_string(), root_.to_string());
    LOGGER->trace("value: \"{}\"", value);
    if (!json_->contains(key)) {

    }
    (*json_)[key] = value;
}
