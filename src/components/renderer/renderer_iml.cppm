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

    void BaseRenderer::draw() {
    }

    void BaseRenderer::set_target(std::shared_ptr<sf::RenderTarget> target) {
        target_ = target;
    }

    void BaseRenderer::set_playground(std::shared_ptr<playground::BasePlayGround> playground) {
        playground_ = playground;
    }
}
