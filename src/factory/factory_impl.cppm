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
#include <__ranges/rend.h>

#include "tools/logger/logger_define.hpp"
export module bik.factory:impl;
import :interface;
import bik.logger;
import bik.ui;
import bik.window;
import bik.playground;
import bik.renderer;
import bik.imgui_wrapper;
namespace bik::factory {
    BaseFactory::BaseFactory() {
        LOGGER->info("Factory::Factory()");
    }

    BaseFactory::~BaseFactory() {
        LOGGER->info("Factory::~Factory()");
    }

    void BaseFactory::creation() {
        LOGGER->info("Factory::creation()");
        build_window();
        build_ui();
        build_playground();
        build_renderer();
        build_imgui_wrapper();
        imgui_wrapper_->set_window(window_);
        renderer_->set_playground(playground_);
        renderer_->set_target(window_);
        ui_->set_playground(playground_);
        ui_->set_window(window_);
        ui_->set_renderer(renderer_);
        ui_->set_imgui_wrapper(imgui_wrapper_);
    }

    std::shared_ptr<window::BaseWindow> BaseFactory::window() const {
        return window_;
    }

    std::shared_ptr<ui::BaseUI> BaseFactory::ui() const {
        return ui_;
    }

    std::shared_ptr<playground::BasePlayGround> BaseFactory::playground() const {
        return playground_;
    }

    std::shared_ptr<renderer::BaseRenderer> BaseFactory::renderer() const {
        return renderer_;
    }

    std::shared_ptr<imguiwrapper::BaseImGuiWrapper> BaseFactory::imgui_wrapper() const {
        return imgui_wrapper_;
    }

    void BaseFactory::build_window() {
        LOGGER->info("Factory::create_window()");
        pre_build_window();
        window_ = std::make_shared<window::BaseWindow>();
    }

    void BaseFactory::build_ui() {
        LOGGER->info("Factory::create_ui()");
        pre_build_ui();
        ui_ = std::make_shared<ui::BaseUI>();
    }

    void BaseFactory::build_playground() {
        pre_build_playground();
        playground_ = std::make_shared<playground::BasePlayGround>();
    }

    void BaseFactory::build_renderer() {
        pre_build_renderer();
        renderer_ = std::make_shared<renderer::BaseRenderer>();
    }

    void BaseFactory::build_imgui_wrapper() {
        imgui_wrapper_ = std::make_shared<imguiwrapper::BaseImGuiWrapper>();
    }


    void BaseFactory::pre_build_window() {
    }

    void BaseFactory::pre_build_ui() {
        if (window_ == nullptr) {
            LOGGER->error("Window est null et doit être créé avant UI");
        }
    }

    void BaseFactory::pre_build_playground() {
    }

    void BaseFactory::pre_build_renderer() {
    }

    void BaseFactory::pre_build_imgui_wrapper() {
    }

    void BaseFactory::clear() {
        LOGGER->info("Factory::clear()");
        window_ = nullptr;
        ui_ = nullptr;
        playground_ = nullptr;
        renderer_ = nullptr;
        imgui_wrapper_ = nullptr;
    }
}
