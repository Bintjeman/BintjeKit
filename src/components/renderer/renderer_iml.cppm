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
#include <SFML/Graphics/RenderTarget.hpp>
export module bik.renderer:impl;
import :interface;
import bik.playground;
namespace bik::renderer {
    BaseRenderer::BaseRenderer() {
    }

    BaseRenderer::~BaseRenderer() {
    }

    void BaseRenderer::draw() {
    }

    void BaseRenderer::set_target(std::shared_ptr<sf::RenderTarget> target) {
        target_ = target;
    }

    void BaseRenderer::set_playground(std::shared_ptr<playground::BasePlayGround> playground) {
        playground_ = playground;
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
}
