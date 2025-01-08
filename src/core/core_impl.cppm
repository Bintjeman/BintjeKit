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
#include <nlohmann/json.hpp>
#include "tools/logger/logger_define.hpp"
export module bik.core:impl;
import :interface;
import bik.window;
import bik.ui;
import bik.factory;
import bik.logger;
import bik.settings;
namespace bik::core {
    [[deprecated("Use the constructor with a unique_ptr<factory::Factory> instead")]]
    Core::Core() {
        LOGGER->info("Core::Core()");
        factory_ = std::make_unique<factory::BaseFactory>();
    }

    Core::Core(std::unique_ptr<factory::BaseFactory> factory) {
        LOGGER->info("Core::Core(std::unique_ptr<factory::Factory> factory)");
        factory_ = std::move(factory);
    }

    Core::~Core() {
        LOGGER->info("Core::~Core()");
    }

    void Core::configure() {
        LOGGER->info("Core::configure()");
        create_components();
        settings_.load("settings.json");
        auto window_settings = settings_.create_child("/Window"_json_pointer);
        window_->configure(window_settings);
        configure_inner();
    }

    void Core::initialize() {
        LOGGER->info("Core::initialize()");
        window_->initialize();
    }

    void Core::run() {
        LOGGER->info("Core::run()");
        window_->open();
        while (window_->isOpen()) {
            while (const std::optional event = window_->pollEvent()) {
                // "close requested" event: we close the window
                if (event->is<sf::Event::Closed>())
                    window_->close();
            }
            window_->update();
        }
    }

    void Core::finalize() {
        LOGGER->info("Core::finalize()");
        window_->finalize();
        settings_.save("settings.json");
    }

    void Core::create_components() {
        LOGGER->info("Core::create_components()");
        factory_->creation();
        window_ = factory_->window();
        ui_ = factory_->ui();
        factory_->clear();
    }

    void Core::configure_inner() {
        LOGGER->info("Core::configure_inner()");
    }
}
