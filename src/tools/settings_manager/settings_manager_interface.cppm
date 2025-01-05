/*!
 * @file settings_manager_interface.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
export module settings_manager:interface;
namespace bik::config {

    using Json = nlohmann::json;

    // Classe Node : Interface pour manipuler directement les branches JSON
    export class Node {
    public:
        Node(std::shared_ptr<Json> json, const std::string& root = "");

        template <typename T>
        T get(const std::string& key, const T& defaultValue) const;

        template <typename T>
        T get_or_set(const std::string& key, const T& defaultValue);

        template <typename T>
        void set(const std::string& key, const T& value);

        Node create_child(const std::string& key);

        Json& raw() { return *json_; }
        const Json& raw() const { return *json_; }

        // Trouver une racine finale propre pour éviter les confusions avec /
        std::string build_full_key(const std::string& key) const;

    protected:
        std::shared_ptr<Json> json_;
        std::string root_;
    };

    // Classe Settings
    export class Settings : public Node {
    public:
        Settings();

        void load(const std::string& filepath);
        void save(const std::string& filepath) const;

    };

    // Classe Child : Une sous-branche JSON
    export class Child : public Node {
    public:
        Child(std::shared_ptr<Json> json, const std::string& root);
    };
}