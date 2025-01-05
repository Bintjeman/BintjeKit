/*!
 * @file core_impl.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <iostream>
export module core:impl;
import :interface;
import window;
import factory;
import logger;
namespace bik::core {
    Core::Core() {
        logger::getLogger()->info("Core::Core()");
        factory_ = std::make_unique<factory::Factory>();
        initialize();
    }

    Core::Core(std::unique_ptr<factory::Factory> factory) {
        logger::getLogger()->info("Core::Core(std::unique_ptr<factory::Factory> factory)");
        factory_ = std::move(factory);
        initialize();
    }

    Core::~Core() {
        logger::getLogger()->info("Core::~Core()");
    }

    void Core::configure() {
        logger::getLogger()->info("Core::configure()");
    }

    void Core::initialize() {
        logger::getLogger()->info("Core::initialize()");
        create_components();
    }

    void Core::run() {
        logger::getLogger()->info("Core::run()");
    }

    void Core::finalize() {
        logger::getLogger()->info("Core::finalize()");
    }

    void Core::create_components() {
        logger::getLogger()->info("Core::create_components()");
        window_ = factory_->create_window();
    }

    void Core::hw() {
        std::cout << "Je suis core de bintjeKit !" << std::endl;
        window_->hw();
    }
}
