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
import bik.window;
export module factory;
import bik.factory;
export import  window;
export class Factory : public bik::factory::BaseFactory {
public:
    std::shared_ptr<bik::window::BaseWindow> create_window() override {
        return std::make_shared<Window>();
    }
};
