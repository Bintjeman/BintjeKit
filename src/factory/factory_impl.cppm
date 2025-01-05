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
// #include <spdlog/spdlog.h>
export module factory:impl;
import :interface;
import window;
import logger;
namespace bik::factory {
    Factory::Factory() {
        logger::getLogger()->info("Factory::Factory()");
    }

    Factory::~Factory() {
        logger::getLogger()->info("Factory::~Factory()");
    }

    std::shared_ptr<window::Window> Factory::create_window() {
        logger::getLogger()->info("Factory::create_window()");
        return std::make_shared<window::Window>();
    }
}
