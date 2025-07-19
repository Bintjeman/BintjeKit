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
    class BackgroundRenderer final : bnjkit::renderer::IRenderSystem {
    public:
        BackgroundRenderer();
        ~BackgroundRenderer();
        void initialize(bnjkit::engine::IEngine& engine) override;
        void update(bnjkit::engine::IEngine& engine) override;
        void render(sf::RenderTarget& target) const override;
        [[nodiscard]] std::string name() const override;
    };
} // bil
#endif //BACKGROUND_RENDERER_HPP
