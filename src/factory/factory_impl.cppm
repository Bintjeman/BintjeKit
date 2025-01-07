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
import bik.window;
import bik.ui;
import bik.logger;
namespace bik::factory {
    BaseFactory::BaseFactory() {
        LOGGER->info("Factory::Factory()");
    }

    BaseFactory::~BaseFactory() {
        LOGGER->info("Factory::~Factory()");
    }

    void BaseFactory::creation() {
        LOGGER->info("Factory::creation()");
        build_ui();
        build_window();
    }

    std::shared_ptr<window::BaseWindow> BaseFactory::get_window() const {
        return window_;
    }

    std::shared_ptr<ui::BaseUI> BaseFactory::get_ui() const {
        return ui_;
    }

    void BaseFactory::build_window() {
        LOGGER->info("Factory::create_window()");
        window_ = std::make_shared<window::BaseWindow>(*ui_);
    }

    void BaseFactory::build_ui() {
        LOGGER->info("Factory::create_ui()");
        ui_ = std::make_shared<ui::BaseUI>();
    }

    void BaseFactory::clear() {
        LOGGER->info("Factory::clear()");
        window_ = nullptr;
        ui_ = nullptr;
    }
}
