/*!
 * @author bintjeman
 * @date 19.07.25
 * @name ball_renderer.hpp
 */

#ifndef BALL_RENDERER_HPP
#define BALL_RENDERER_HPP
#pragma once

#include <bintjekit/renderer/i_render_system.hpp>

namespace bil {
    class Billard;
    class BallRenderer : public bnjkit::renderer::IRenderSystem {
    public:
        ~BallRenderer() override;
        void initialize(bnjkit::engine::IEngine& engine) override;
        void render(sf::RenderTarget& target) const override;
        [[nodiscard]] std::string name() const override;
        private:
        Billard* m_billard;
    };
} // bil

#endif //BALL_RENDERER_HPP
