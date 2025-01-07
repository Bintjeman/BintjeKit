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
#include <filesystem>
export module settings:interface;
import :node;
namespace bik::config {
    export class Settings : public Node {
    public:
        Settings();
        void load(const std::filesystem::path &filepath);
        void save(const std::filesystem::path &filepath) const;

    private:
        std::filesystem::path current_path_;
    };

    export using Child = Node;
}
