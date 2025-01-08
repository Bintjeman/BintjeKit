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
export module bik.renderer:impl;
import :interface;
namespace bik::renderer {
    BaseRenderer::BaseRenderer() {
    }

    void BaseRenderer::set_target(std::shared_ptr<sf::RenderTarget> target) {
        target_ = target;
    }

    void BaseRenderer::set_playground(std::shared_ptr<playground::BasePlayGround> playground) {
        playground_ = playground;
    }
}
