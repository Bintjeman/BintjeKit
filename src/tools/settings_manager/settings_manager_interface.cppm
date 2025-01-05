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
    // Alias pour simplifier l'utilisation
    using Json = nlohmann::json;

    // Classe Node : Classe de base pour manipuler une branche JSON
    export class Node {
    public:
        // Constructeur principal
        Node(std::shared_ptr<Json> json, const std::string &root = "/");

        // Get : Récupère une valeur avec une valeur par défaut
        template<typename T>
        T get(const std::string &key, const T &defaultValue) const;

        // Get ou insérer la valeur par défaut si elle n'existe pas
        template<typename T>
        T get_or_set(const std::string &key, const T &defaultValue);

        // Set : Définit une valeur
        template<typename T>
        void set(const std::string &key, const T &value);

    protected:
        std::shared_ptr<Json> json_; // Pointeur partagé sur l'objet JSON
        std::string root_; // Racine relative de la sous-arborescence JSON
    };

    // Classe Settings : Gestionnaire principal de configuration
    export class Settings : public Node {
    public:
        Settings();
        // Charger un JSON depuis un fichier
        void load(const std::string &filepath);
        // Sauvegarder dans un fichier JSON
        void save(const std::string &filepath) const;

        // Créer un enfant lié à une branche spécifique
        Node create_child(const std::string &key);
    };

    // Classe Child : Sous-racine d'une configuration JSON
    export class Child : public Node {
    public:
        Child(std::shared_ptr<Json> json, const std::string &root);
    };
}
