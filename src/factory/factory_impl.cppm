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
#include "tools/logger/logger_define.hpp"
export module bik.factory:impl;
import :interface;
import bik.logger;
import bik.ui;
import bik.window;
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
    }

    std::shared_ptr<window::BaseWindow> BaseFactory::window() const {
        return window_;
    }

    std::shared_ptr<ui::BaseUI> BaseFactory::ui() const {
        return ui_;
    }

    void BaseFactory::build_window() {
        LOGGER->info("Factory::create_window()");
        pre_build_window();
        window_ = std::make_shared<window::BaseWindow>();
    }

    void BaseFactory::build_ui() {
        LOGGER->info("Factory::create_ui()");
        pre_build_ui();
        ui_ = std::make_shared<ui::BaseUI>(*window_);
    }

    void BaseFactory::pre_build_window() {

    }

    void BaseFactory::pre_build_ui() {
        if (window_ == nullptr) {
            LOGGER->error("Window est null et doit être créé avant UI");
        }
    }

    void BaseFactory::clear() {
        LOGGER->info("Factory::clear()");
        window_ = nullptr;
        ui_ = nullptr;
    }
}
