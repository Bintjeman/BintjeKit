/*!
 * @file node.cppm
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
export module bik.settings:node;
namespace bik::settings {
    export class Node {
    public:
        explicit Node(const std::shared_ptr<nlohmann::json> &json = nullptr,
                      const nlohmann::json::json_pointer &root = ""_json_pointer);
        ~Node();

        template<typename T>
        T get(const nlohmann::json::json_pointer &key, const T &defaultValue) const;
        template<typename T>
        T get(const nlohmann::json::json_pointer &key) const;
        template<typename T>
        T get_or_set(const nlohmann::json::json_pointer &key, const T &defaultValue);
        template<typename T>
        void set(const nlohmann::json::json_pointer &key, const T &value);
        Node create_child(const nlohmann::json::json_pointer &key);

        [[nodiscard]] const nlohmann::json &raw() const { return *json_; }

    protected:
        std::shared_ptr<nlohmann::json> json_;
        nlohmann::json::json_pointer root_;

    private:
        template<typename T>
        void set_inner(const nlohmann::json::json_pointer &key, const T &value);

        static int node_counter;
    };
}
