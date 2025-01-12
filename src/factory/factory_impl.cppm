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
        build_ui();
        build_playground();
        build_renderer();
        auto renderer = dynamic_cast<renderer::BaseRenderer *>(components_.at("renderer").get());
        auto window = dynamic_cast<window::BaseWindow *>(components_.at("window").get());
        auto ui = dynamic_cast<ui::BaseUI *>(components_.at("ui").get());
        auto playground = dynamic_cast<playground::BasePlayGround *>(components_.at("playground").get());
    }

    std::unique_ptr<window::BaseWindow> BaseFactory::consume_window() {
        return std::move(
            std::unique_ptr<window::BaseWindow>(static_cast<window::BaseWindow *>(components_["window"].release())));
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
        components_["ui"] = std::make_unique<ui::BaseUI>();
    }

    void BaseFactory::build_playground() {
        pre_build_playground();
        components_["playground"] = std::make_unique<playground::BasePlayGround>();
    }

    void BaseFactory::build_renderer() {
        pre_build_renderer();
        auto window = dynamic_cast<window::BaseWindow *>(components_["window"].get());
        if (!window) {
            LOGGER->error("Impossible de créer le Renderer : la fenêtre est invalide ou introuvable.");
            return;
        }
        // Récupérer "playground".
        auto &playground = *dynamic_cast<playground::BasePlayGround *>(components_["playground"].get());
        // Construction du renderer avec la référence à "RenderTarget".
        components_["renderer"] = std::make_unique<renderer::BaseRenderer>(window, playground);
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
