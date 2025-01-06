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
#include <nlohmann/detail/json_pointer.hpp>
#include <memory>
#include <string>
export module settings_manager:interface;
namespace bik::config {
    using Json = nlohmann::json;

    // Classe Node : Interface pour manipuler directement les branches JSON
    export class Node {
    public:
        Node();
        Node(std::shared_ptr<Json> json, const nlohmann::json::json_pointer& root = "/"_json_pointer);

        template<typename T>
        T get(const nlohmann::json::json_pointer &key, const T &defaultValue) const;

        template<typename T>
        T get_or_set(const nlohmann::json::json_pointer &key, const T &defaultValue);

        template<typename T>
        void set(const nlohmann::json::json_pointer &key, const T &value);

        Node create_child(const nlohmann::json::json_pointer &key);
        int node_number();

        Json &raw() { return *json_; }
        const Json &raw() const { return *json_; }

    protected:
        nlohmann::json::json_pointer make_from_root_key(const nlohmann::json::json_pointer &key) const;

        std::shared_ptr<Json> json_;
        nlohmann::json::json_pointer root_;
    };

    // Classe Settings
    export class Settings : public Node {
    public:
        Settings();

        void load(const std::string &filepath);
        void save(const std::string &filepath) const;
    };
}
