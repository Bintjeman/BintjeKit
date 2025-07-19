/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_renderer.cpp
 */

#include "bintjekit/renderer/default_renderer.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "bintjekit/utils/fmt_sfml/fmt_sfml.hpp"

namespace bnjkit::renderer {
    DefaultRenderSystem::DefaultRenderSystem(): IRenderSystem() {
        m_logger->warn("DefaultRenderSystem created");
    }
    DefaultRenderSystem::~DefaultRenderSystem() {
        m_logger->warn("DefaultRenderSystem destroyed");
    }
    void DefaultRenderSystem::render(sf::RenderTarget& target) const {
        auto calls = ++ m_render_calls;
        if (calls == 1) {
            m_logger->error("DefaultRenderSystem render called");
        }
        constexpr float size_x = 100.f;
        constexpr float size_y = 100.f;
        constexpr float repetition = 1000.f;
        int x_count = 0;
        int y_count = 0;
        sf::RectangleShape rect(sf::Vector2f(size_x, size_y));
        for (auto x = - size_x * repetition / 2.f; x < repetition / 2.f; x += size_x) {
            ++ x_count;
            for (auto y = - size_y * repetition / 2.f; y < repetition / 2.f; y += size_y) {
                ++ y_count;
                rect.setPosition({x, y});
                unsigned char red = 0;
                unsigned char green = 0;
                unsigned char blue = 255;
                unsigned char alpha = 255;
                if (x_count % 2 == 0) {
                    red = 255;
                }
                if (y_count % 2 == 0) {
                    green = 255;
                }
                rect.setFillColor({red, green, blue, alpha});
                target.draw(rect);
            }
        }
    }
    std::string DefaultRenderSystem::name() const {
        return "DefaultRenderSystem";
    }
    DefaultRenderer::DefaultRenderer() {
        m_logger->warn("DefaultRenderer created");
    }
    DefaultRenderer::~DefaultRenderer() {
        m_logger->warn("DefaultRenderer destroyed");
    }
    void DefaultRenderer::initialise() {
        m_logger->error("DefaultRenderer initialise");
        IRenderer::initialise();
        add_render_system(
            std::make_unique<DefaultRenderSystem>(),
            RenderLayer::BACKGROUND
        );
    }
    std::string DefaultRenderer::name() const {
        return "DefaultRenderer";
    }
}
