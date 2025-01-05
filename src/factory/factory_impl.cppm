/*!
 * @file factory_impl.cppm
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
export module factory:impl;
import :interface;
import window;
namespace bik::factory {
    Factory::Factory() {
    }

    Factory::~Factory() {
    }

    std::shared_ptr<window::Window> Factory::create_window() {
        return std::make_shared<window::Window>();
    }
}
