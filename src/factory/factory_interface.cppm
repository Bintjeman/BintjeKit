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
export module factory:interface;
export import window;
namespace bik::factory {
    export class Factory {
        public:
        Factory();
        virtual ~Factory();
        virtual std::shared_ptr<window::Window> create_window();
    };

}
