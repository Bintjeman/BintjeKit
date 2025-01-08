/*!
 * @file factory.cppm
 * @author bintjeman
 * @date 07.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <SFML/Window/Window.hpp>
export module factory;
import bik.factory;
import bik.window;
import window;
namespace tst {
    export class Factory : public bik::factory::BaseFactory {
    public:
        void build_window() override {
            window_ = std::make_shared<Window>();
        }
    };
}
