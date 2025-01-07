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

Node::Node(const std::shared_ptr<nlohmann::json> &json, const nlohmann::json::json_pointer &root) {
    root_ = root;
    if (json == nullptr) {
        json_ = std::make_shared<nlohmann::json>();
        *json_ = nlohmann::json::parse("{}");
    } else {
        json_ = json;
    }
    LOGGER->info("Node::Node(const std::shared_ptr<Json>& json, const nlohmann::json::json_pointer &root)");
    LOGGER->info("json shared counter: {}", json_.use_count());
    LOGGER->info("root: {}", root_.to_string());
    LOGGER->info("json: {}", json_->dump(4));
}

template<typename T>
T Node::get(const nlohmann::json::json_pointer &key, const T &defaultValue) const {
    auto ptr = root_ / key;
    LOGGER->info("Node::get(const nlohmann::json::json_pointer &key, const T &defaultValue) const");
    LOGGER->info("key {} / root {} = ptr: {}", key.to_string(), root_.to_string(), ptr.to_string());
    if (!json_->contains(ptr)) {
        return defaultValue;
    } else {
        return json_->at(ptr).get<T>();
    }
}

template<typename T>
T Node::get_or_set(const nlohmann::json::json_pointer &key, const T &defaultValue) {
}

template<typename T>
void Node::set(const nlohmann::json::json_pointer &key, const T &value) {
    auto ptr = root_ / key;
    if (!json_->contains(ptr)) {
    }
    (*json_)[ptr] = value;
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
