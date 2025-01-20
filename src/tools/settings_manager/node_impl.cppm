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
export module bik.settings:node_impl;
import :node;
import :nlohmann_extension;
namespace bik::settings {
    int Node::node_counter = 0;
    Node::Node(const std::shared_ptr<nlohmann::json> &json,
               const nlohmann::json::json_pointer &root) {
        LOGGER->info(
            "Node::Node(const std::shared_ptr<Json>& json, const nlohmann::json::json_pointer &root)");
        node_counter++;
        root_ = root;
        if (json == nullptr) {
            json_ = std::make_shared<nlohmann::json>();
            *json_ = nlohmann::json::parse("{}");
        } else {
            json_ = json;
        }
    }

    Node::~Node() {
        LOGGER->info("Node::~Node()");
        node_counter--;
    }

    template<typename T>
    T Node::get(const nlohmann::json::json_pointer &key, const T &defaultValue) const {
        auto ptr = root_ / key;
        if (!json_->contains(ptr)) {
            return defaultValue;
        } else {
            return json_->at(ptr).get<T>();
        }
    }

    template<typename T>
    T Node::get(const nlohmann::json::json_pointer &key) const {
        auto ptr = root_ / key;
        return json_->at(ptr).get<T>();
    }

    template<typename T>
    T Node::get_or_set(const nlohmann::json::json_pointer &key, const T &defaultValue) {
        auto ptr = root_ / key;
        if (!json_->contains(ptr)) {
            (*json_)[root_ / key] = defaultValue;
            return defaultValue;
        } else {
            return json_->at(ptr).get<T>();
        }
    }

    template<typename T>
    void Node::set(const nlohmann::json::json_pointer &key, const T &value) {
        (*json_)[root_ / key] = value;
    }

    Node Node::create_child(const nlohmann::json::json_pointer &key) {
        LOGGER->info("Node::create_child(const nlohmann::json::json_pointer &key)");
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
        if (!json_->contains(key)) {
        }
        (*json_)[key] = value;
    }
}
