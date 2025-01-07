/*!
 * @file factory_interface.cppm
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
export module bik.factory:interface;
export import bik.window;
namespace bik::factory {
    export class BaseFactory {
        public:
        BaseFactory();
        virtual ~BaseFactory();
        virtual std::shared_ptr<window::BaseWindow> create_window();
    };

}
