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
#include <map>
#include "tools/logger/logger_define.hpp"
export module bik.factory:impl;
import :interface;
import bik.common;
import bik.logger;
import bik.ui;
import bik.window;
import bik.playground;
import bik.renderer;
namespace bik::factory {
    BaseFactory::BaseFactory() {
        LOGGER->info("Factory::Factory()");
    }

    BaseFactory::~BaseFactory() {
        LOGGER->info("Factory::~Factory()");
    }

    /*!
     * @note
     * Liste des dépendances des classes
     *  - Window ne dépend de rien
     *  - Playground ne dépends de rien
     *  - Renderer dépend de playground et window
     *  - UI Dépend de playground et renderer
     */
    void BaseFactory::creation() {
        LOGGER->info("Factory::creation()");
        build_window();
        build_playground();
        build_renderer();
        build_ui();
    }

    std::unique_ptr<window::BaseWindow> BaseFactory::consume_window() {
        return std::move(
            std::unique_ptr<window::BaseWindow>(
                static_cast<window::BaseWindow *>(components_["window"].release())));
    }

    std::unique_ptr<ui::BaseUI> BaseFactory::consume_ui() {
        return std::move(
            std::unique_ptr<ui::BaseUI>(static_cast<ui::BaseUI *>(components_["ui"].release())));
    }

    std::unique_ptr<playground::BasePlayGround> BaseFactory::consume_playground() {
        return std::move(
            std::unique_ptr<playground::BasePlayGround>(
                static_cast<playground::BasePlayGround *>(components_["playground"].release())));
    }

    std::unique_ptr<renderer::BaseRenderer> BaseFactory::consume_renderer() {
        return std::move(
            std::unique_ptr<renderer::BaseRenderer>(
                static_cast<renderer::BaseRenderer *>(components_["renderer"].release())));
    }

    void BaseFactory::build_window() {
        LOGGER->info("Factory::create_window()");
        pre_build_window();
        components_["window"] = std::make_unique<window::BaseWindow>();
    }

    void BaseFactory::build_ui() {
        LOGGER->info("Factory::create_ui()");
        pre_build_ui();
        auto window = window_ptr_from_unique();
        auto playground = playground_ptr_from_unique();
        auto renderer = renderer_ptr_from_unique();
        components_["ui"] = std::make_unique<ui::BaseUI>(window, renderer, playground);
    }

    void BaseFactory::build_playground() {
        pre_build_playground();
        components_["playground"] = std::make_unique<playground::BasePlayGround>();
    }

    void BaseFactory::build_renderer() {
        pre_build_renderer();
        auto window = window_ptr_from_unique();
        auto playground = playground_ptr_from_unique();
        components_["renderer"] = std::make_unique<renderer::BaseRenderer>(window, playground);
    }

    window::BaseWindow *BaseFactory::window_ptr_from_unique() {
        return dynamic_cast<window::BaseWindow *>(components_.at("window").get());
    }

    ui::BaseUI *BaseFactory::ui_ptr_from_unique() {
        return dynamic_cast<ui::BaseUI *>(components_.at("ui").get());
    }

    playground::BasePlayGround *BaseFactory::playground_ptr_from_unique() {
        return dynamic_cast<playground::BasePlayGround *>(components_.at("playground").get());
    }

    renderer::BaseRenderer *BaseFactory::renderer_ptr_from_unique() {
        return dynamic_cast<renderer::BaseRenderer *>(components_.at("renderer").get());
    }

    window::BaseWindow &BaseFactory::window_ref_from_unique() {
        auto window = dynamic_cast<window::BaseWindow *>(components_["window"].get());
        if (!window) {
            LOGGER->error(
                "La fenêtre est invalide ou introuvable.");
        }
        return *window;
    }

    ui::BaseUI &BaseFactory::ui_ref_from_unique() {
        auto ui = dynamic_cast<ui::BaseUI *>(components_["ui"].get());
        if (!ui) {
            LOGGER->error(
                "L'ui est invalide ou introuvable.");
        }
        return *ui;
    }

    playground::BasePlayGround &BaseFactory::playground_ref_from_unique() {
        auto playground = dynamic_cast<playground::BasePlayGround *>(components_["playground"].
            get());
        if (!playground) {
            LOGGER->error(
                "Le playground est invalide ou introuvable.");
        }
        return *playground;
    }

    renderer::BaseRenderer &BaseFactory::renderer_ref_from_unique() {
        auto renderer = dynamic_cast<renderer::BaseRenderer *>(components_["renderer"].get());
        if (!renderer) {
            LOGGER->error(
                "Le renderer est invalide ou introuvable.");
        }
        return *renderer;
    }

    void BaseFactory::pre_build_window() {
    }

    void BaseFactory::pre_build_ui() {
        if (components_["window"] == nullptr) {
            LOGGER->error("Window est null et doit être créé avant UI");
        }
    }

    void BaseFactory::pre_build_playground() {
    }

    void BaseFactory::pre_build_renderer() {
    }

    void BaseFactory::clear() {
        LOGGER->info("Factory::clear()");
        components_.clear();
    }
}
