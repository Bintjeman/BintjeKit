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
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/detail/json_pointer.hpp>
export module core:impl;
import :interface;
import window;
import factory;
import logger;
import settings_manager;
namespace bik::core {
    Core::Core() {
        if (!logger::getLogger()) {
            logger::init();
        }
        logger::getLogger()->info("Core::Core()");
        factory_ = std::make_unique<factory::Factory>();
        create_components();
    }

    Core::Core(std::unique_ptr<factory::Factory> factory) {
        logger::getLogger()->info("Core::Core(std::unique_ptr<factory::Factory> factory)");
        factory_ = std::move(factory);
        create_components();
    }

    Core::~Core() {
        logger::getLogger()->info("Core::~Core()");
    }

    void Core::configure() {
        logger::getLogger()->info("Core::configure()");
        std::cout << "Settings node number: " << settings_.node_number() << std::endl;
        settings_.load("settings.json");
        auto window_settings = settings_.create_child("/Window"_json_pointer);
        std::cout << "Settings node number: " << settings_.node_number() << std::endl;
        window_->configure(window_settings);
        std::cout << "Settings node number: " << settings_.node_number() << std::endl;
        configure_inner();
        std::cout << "Settings node number: " << settings_.node_number() << std::endl;
    }

    void Core::initialize() {
        logger::getLogger()->info("Core::initialize()");
        create_components();
        window_->initialize();
    }

    void Core::run() {
        logger::getLogger()->info("Core::run()");
        window_->open();
        while (window_->isOpen()) {
            while (const std::optional event = window_->pollEvent()) {
                // "close requested" event: we close the window
                if (event->is<sf::Event::Closed>())
                    window_->close();
            }
        }
    }

    void Core::finalize() {
        logger::getLogger()->info("Core::finalize()");
        std::cout << "Settings node number: " << settings_.node_number() << std::endl;
        settings_.save("settings.json");
    }

    void Core::create_components() {
        logger::getLogger()->info("Core::create_components()");
        window_ = factory_->create_window();
    }
    void Core::configure_inner() {
        logger::getLogger()->info("Core::configure_inner()");
    }

    void Core::hw() {
        std::cout << "Je suis core de bintjeKit !" << std::endl;
        window_->hw();
    }
}
