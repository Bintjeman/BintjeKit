/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_renderer.cpp
 */

#include "bintjekit/renderer/default_renderer.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace bnjkit::renderer {
    DefaultRenderSystem::DefaultRenderSystem(): IRenderSystem() {
        m_logger->warn("DefaultRenderSystem created");
    }
    DefaultRenderSystem::~DefaultRenderSystem() {
        m_logger->warn("DefaultRenderSystem destroyed");
    }
    void DefaultRenderSystem::render(sf::RenderTarget& target) const {
        sf::RectangleShape rect(sf::Vector2f(100, 100));
        rect.setFillColor(sf::Color::Red);
        target.draw(rect);
    }
    std::string DefaultRenderSystem::name() const {
        return "DefaultRenderSystem";
    }
    DefaultRenderer::DefaultRenderer() {
        m_logger->warn("DefaultRenderer created");
        // Ajouter le système de rendu par défaut
        add_render_system(
            std::make_unique<DefaultRenderSystem>(),
            RenderLayer::BACKGROUND
        );
    }
    DefaultRenderer::~DefaultRenderer() {
        m_logger->warn("DefaultRenderer destroyed");
    }
    void DefaultRenderer::render_scene() {
        IRenderer::render_scene();
    }
    void DefaultRenderer::render_gui() {
        IRenderer::render_gui();
    }
}
