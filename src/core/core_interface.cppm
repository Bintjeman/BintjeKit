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
export import factory;
namespace bik::core {
    export class Core {
    public:
        Core(std::unique_ptr<factory::Factory> factory);

        ~Core();

        void hw();

    private:
        std::unique_ptr<factory::Factory> factory_;
        std::shared_ptr<window::Window> window_;
    };
}
