/*!
 * @author bintjeman
 * @date 19.07.25
 * @name background_renderer.hpp
 */

#ifndef BACKGROUND_RENDERER_HPP
#define BACKGROUND_RENDERER_HPP
#pragma once
#include "bintjekit/renderer/i_render_system.hpp"

namespace bil {
    class Billard;
    class BackgroundRenderer final : public bnjkit::renderer::IRenderSystem {
    public:
        BackgroundRenderer();
        ~BackgroundRenderer() override;
        void initialize(bnjkit::engine::IEngine& engine) override;
        void update(bnjkit::engine::IEngine& engine) override;
        void render(sf::RenderTarget& target) const override;
        [[nodiscard]] std::string name() const override;
        private:
        Billard* m_engine;
    };
} // bil
#endif //BACKGROUND_RENDERER_HPP
