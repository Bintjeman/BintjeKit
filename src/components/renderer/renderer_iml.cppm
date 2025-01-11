/*!
 * @file renderer_iml.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <filesystem>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <nlohmann/json.hpp>
#include "tools/logger/logger_define.hpp"
export module bik.renderer:impl;
import :interface;
import bik.playground;
import bik.common;
import bik.d2;
import bik.logger;
namespace bik::renderer {
    BaseRenderer::BaseRenderer() {
        LOGGER->info("Renderer::Renderer()");
    }

    BaseRenderer::~BaseRenderer() {
        LOGGER->info("Renderer::~Renderer()");
    }

    void BaseRenderer::configure(config::Child settings) {
        LOGGER->info("Renderer::configure()");
        settings_ = settings;
    }

    void BaseRenderer::initialize() {
        LOGGER->info("Renderer::initialize()");
    }

    void BaseRenderer::update() {
    }

    void BaseRenderer::finalize() {
        LOGGER->info("Renderer::finalize()");
    }

    void BaseRenderer::draw() {
    }

    void BaseRenderer::set_target(std::shared_ptr<sf::RenderTarget> target) {
        target_ = target;
        main_view_ = target->getView();
        playground_view_ = main_view_;
        ui_view_ = main_view_;
        target->setView(main_view_);
    }

    void BaseRenderer::set_playground(std::shared_ptr<playground::BasePlayGround> playground) {
        playground_ = playground;
    }

    void BaseRenderer::set_core_info_provider(common::BaseCoreInfoProvider *core_info_provider) {
        core_info_provider_ = core_info_provider;
    }

    void BaseRenderer::set_view(sf::View view) {
        target_->setView(view);
    }

    void BaseRenderer::camera_move(sf::Vector2f offset) {
        playground_view_.move(offset);
    }

    void BaseRenderer::camera_zoom(float zoom) {
        playground_view_.zoom(zoom);
    }

    void BaseRenderer::reframe() {
        auto playground_boundaries = playground_->boundaries();
        auto target_size = target_->getSize();
        auto playground_ratio = d2::ratio(playground_boundaries.size);
        auto target_ratio = d2::ratio(sf::Vector2f(target_size));
        sf::Vector2f view_size;
        if (target_ratio > playground_ratio) {
            view_size.x = playground_boundaries.size.y * target_ratio;
            view_size.y = playground_boundaries.size.y;
        } else {
            view_size.x = playground_boundaries.size.x;
            view_size.y = playground_boundaries.size.x * target_ratio;
        }
        playground_view_.setSize(view_size);
        playground_view_.setCenter(playground_boundaries.position + playground_boundaries.size / 2.f);
    }
}
