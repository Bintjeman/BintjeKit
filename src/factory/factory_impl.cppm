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
export module bik.factory:impl;
import :interface;
import bik.window;
import bik.logger;
namespace bik::factory {
    BaseFactory::BaseFactory() {
        logger::getLogger()->info("Factory::Factory()");
    }

    BaseFactory::~BaseFactory() {
        logger::getLogger()->info("Factory::~Factory()");
    }

    std::shared_ptr<window::BaseWindow> BaseFactory::create_window() {
        logger::getLogger()->info("Factory::create_window()");
        return std::make_shared<window::BaseWindow>();
    }
}
