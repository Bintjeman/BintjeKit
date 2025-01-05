/*!
 * @file factory_child.cppm
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
export module factory_child;
import factory;
import window_child;
namespace min {
    export class Child : public bik::factory::Factory {
    public:
        ~Child() override;
        std::shared_ptr<bik::window::Window> create_window() override;
    };
}
