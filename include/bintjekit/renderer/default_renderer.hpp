/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_renderer.hpp
 */
#ifndef BINTJEKIT_RENDERER_DEFAULT_RENDERER_HPP
#define BINTJEKIT_RENDERER_DEFAULT_RENDERER_HPP
#pragma once
#include "bintjekit/renderer/i_renderer.hpp"
#include "bintjekit/renderer/i_render_system.hpp"

namespace bnjkit::renderer {
    class DefaultRenderSystem : public IRenderSystem {
    public:
        DefaultRenderSystem();
        ~DefaultRenderSystem() override;
        void render(sf::RenderTarget& target) const override;
        [[nodiscard]] std::string name() const override;
    private:
        mutable std::atomic<uint64_t> m_render_calls{0};
    };
    class DefaultRenderer : public IRenderer {
    public:
        DefaultRenderer();
        ~DefaultRenderer() override;
        void initialise() override;
        [[nodiscard]] std::string name() const override;
    };
}
#endif // BINTJEKIT_RENDERER_DEFAULT_RENDERER_HPP
