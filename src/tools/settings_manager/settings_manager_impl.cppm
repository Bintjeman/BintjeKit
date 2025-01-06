/*!
 * @file settings_manager_impl.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <nlohmann/detail/json_pointer.hpp>
export module settings_manager:impl;
import :interface;
namespace bik::config {
    Node::Node() {
        json_ = std::make_shared<Json>();
        *json_ = nlohmann::json::parse("{}");
        root_ = "/"_json_pointer;
    }

    // --- Implémentation de Node ---
    Node::Node(std::shared_ptr<Json> json, const nlohmann::json::json_pointer &root)
        : json_(json), root_(root) {
    }

    template<typename T>
    T Node::get(const nlohmann::json::json_pointer &key, const T &defaultValue) const {
        std::cout << "get at " << key.to_string() << std::endl;
        Json::json_pointer p = make_from_root_key(key);
        if (!json_->contains(p)) {
            std::cout << "key not found\n";
            return defaultValue;
        }
        return json_->at(p).get<T>();
    }

    template<typename T>
    T Node::get_or_set(const nlohmann::json::json_pointer &key, const T &defaultValue) {
        Json::json_pointer p = make_from_root_key(key);
        if (!json_->contains(p)) {
            (*json_)[p] = defaultValue;
        }
        return json_->at(p).get<T>();
    }

    template<typename T>
    void Node::set(const nlohmann::json::json_pointer &key, const T &value) {
        Json::json_pointer p = make_from_root_key(key);
        (*json_)[p] = value;
    }

    config::Node Node::create_child(const nlohmann::json::json_pointer &key) {
        std::cout << "create child at " << key.to_string() << std::endl;
        nlohmann::json::json_pointer p = make_from_root_key(key);
        std::cout << "from root: " << p.to_string() << std::endl;
        if (!json_->contains(p)) {
            std::cout << "key not found\n";
            (*json_)[p] = nlohmann::json::object();
        }
        std::cout << json_->dump(4) << std::endl;
        return Node(json_, p);
    }

    int Node::node_number() {
        return json_.use_count();
    }

    nlohmann::json::json_pointer Node::make_from_root_key(const nlohmann::json::json_pointer &key) const {
        if (root_.empty()) {
            return key;
        } else {
            if (!root_.empty() && key.to_string().front() == '/') {
                return nlohmann::json::json_pointer(root_.to_string() + key.to_string().substr(1));
            } else {
                return root_ / key; // Récupération normale
            }
        }
    }

    // --- Implémentation de Settings ---
    Settings::Settings() : Node(std::make_shared<Json>()) {
        std::cout << "Settings::Settings()" << std::endl;
    }

    void Settings::load(const std::string &filepath) {
        std::cout << "Loading settings from " << filepath << std::endl;
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + filepath);
        }
        file >> *json_;
    }

    void Settings::save(const std::string &filepath) const {
        std::cout << "Saving settings to " << filepath << std::endl;
        std::ofstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'écrire dans le fichier JSON : " + filepath);
        }
        file << json_->dump(4);
        std::cout << json_->dump(4) << std::endl;
    }
} // namespace bik::config
