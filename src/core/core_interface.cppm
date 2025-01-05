/*!
 * @file core_interface.cppm
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
export module core:interface;
import window;
namespace bik::core {
    export class Core {
    public:
        Core();
        void hw();

    private:
        std::shared_ptr<window::Window> window_;
    };
}
