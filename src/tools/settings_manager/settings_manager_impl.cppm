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
#include <sstream>
#include <nlohmann/json.hpp>
export module settings_manager:impl;
import :interface;
namespace bik::config {

    // --- Implémentation de Node ---
    Node::Node(std::shared_ptr<Json> json, const std::string& root)
        : json_(std::move(json)), root_(root) {}

    template <typename T>
    T Node::get(const std::string& key, const T& defaultValue) const {
        Json::json_pointer p(root_ + key);
        if (!json_->contains(p)) {
            return defaultValue;
        }
        return json_->at(p).get<T>();
    }

    template <typename T>
    T Node::get_or_set(const std::string& key, const T& defaultValue) {
        Json::json_pointer p(root_ + key);
        if (!json_->contains(p)) {
            (*json_)[p] = defaultValue;
        }
        return json_->at(p).get<T>();
    }

    template <typename T>
    void Node::set(const std::string& key, const T& value) {
        Json::json_pointer p(root_ + key);
        (*json_)[p] = value;
    }

    std::string Node::build_full_key(const std::string& key) const {
        if (root_.empty() || root_ == "/") {
            return key; // Racine directe : pas besoin de préfixer
        }
        if (key.empty()) {
            return root_; // Si la clé elle-même est vide
        }
        // Ajouter proprement la racine et la clé
        return root_ + (key[0] == '/' ? key : "/" + key);
    }

    Node Node::create_child(const std::string& key) {
        return Node(json_, build_full_key(key));
    }

    // --- Implémentation de Settings ---
    Settings::Settings() : Node(std::make_shared<Json>()) {}

    void Settings::load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + filepath);
        }
        file >> *json_;
    }

    void Settings::save(const std::string& filepath) const {
        std::ofstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'écrire dans le fichier JSON : " + filepath);
        }
        file << json_->dump(4); // Beautification
    }

    // --- Implémentation de Child ---
    Child::Child(std::shared_ptr<Json> json, const std::string& root)
        : Node(std::move(json), root) {}

} // namespace bik::config