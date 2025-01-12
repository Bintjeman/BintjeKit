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
import bik.common;
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
        ui_->set_action_receiver(this);
        renderer_->set_core_info_provider(this);
        settings_.load("settings.json");
        int frame_per_sedond = settings_.get_or_set("/FramePerSedond"_json_pointer, 60);
        int step_per_second = settings_.get_or_set("/StepPerSecond"_json_pointer, 10);
        playground_pulser_.set_frequency(step_per_second);
        renderer_pulser_.set_frequency(frame_per_sedond);
        auto window_settings = settings_.create_child("/Window"_json_pointer);
        window_->configure(window_settings);
        renderer_->configure(settings_.create_child("/Renderer"_json_pointer));
        playground_->configure(settings_.create_child("/Playground"_json_pointer));
    }

    void Core::initialize() {
        LOGGER->info("Core::initialize()");
        window_->initialize();
        imgui_wrapper_->initialize();
        ui_->initialize();
        playground_->initialize();
        renderer_->initialize();
    }

    void Core::run() {
        LOGGER->info("Core::run()");
        window_->open();
        renderer_->reframe();
        while (window_->isOpen()) {
            ui_->update();
            imgui_wrapper_->update();
            if (playground_pulser_()) {
                playground_->update();
            }
            if (renderer_pulser_()) {
                renderer_->draw();
                imgui_wrapper_->render();
            }
            window_->display();
        }
    }

    void Core::finalize() {
        LOGGER->info("Core::finalize()");
        window_->finalize();
        imgui_wrapper_->finalize();
        settings_.save("settings.json");
    }

    void Core::on_close_window() {
        LOGGER->info("Core::on_close_window()");
        finalize();
    }

    double Core::renderer_frequency() const {
        return renderer_pulser_.effective_frequency();
    }

    double Core::playground_frequency() const {
        return playground_pulser_.effective_frequency();
    }

    void Core::create_components() {
        LOGGER->info("Core::create_components()");
        factory_->creation();
        window_ = factory_->window();
        ui_ = factory_->ui();
        playground_ = factory_->playground();
        renderer_ = factory_->renderer();
        imgui_wrapper_ = factory_->imgui_wrapper();
        factory_->clear();

    }
}
