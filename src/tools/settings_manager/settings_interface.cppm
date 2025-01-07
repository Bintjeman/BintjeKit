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
export module bik.settings:interface;
import :node;
namespace bik::config {
    export class Settings : public Node {
    public:
        Settings();
        enum class LoadMode {
            ERROR,
            CREATE,
            NOTHING
        };
        void load(const std::filesystem::path &filepath, LoadMode mode = LoadMode::CREATE);
        void save(const std::filesystem::path &filepath) const;

    private:
        std::filesystem::path current_path_;
    };

    export using Child = Node;
}
