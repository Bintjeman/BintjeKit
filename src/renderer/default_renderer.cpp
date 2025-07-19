/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_renderer.cpp
 */

#include "bintjekit/renderer/default_renderer.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#include "bintjekit/utils/d2/d2.hpp"
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
        constexpr sf::Vector2f centre_pos = {0.f, 0.f};
        constexpr unsigned int ray_count = 15;
        auto sectors = sf::VertexArray(sf::PrimitiveType::TriangleFan, ray_count + 2);
        auto ray = sf::VertexArray(sf::PrimitiveType::LineStrip, ray_count * 2);
        sectors[0] = sf::Vertex(centre_pos, sf::Color::White);
        for (unsigned int i = 0; i <= ray_count; i++) {
            sf::Color color;
            constexpr float radius = 10000.f;
            const unsigned int color_index = (i == ray_count) ? 0 : (i % 3);
            switch (color_index) {
                case 0:
                    color = sf::Color(255, 0, 0); // Rouge
                    break;
                case 1:
                    color = sf::Color(0, 255, 0); // Vert
                    break;
                case 2:
                    color = sf::Color(0, 0, 255); // Bleu
                    break;
                default: ;
            }
            const float angle = static_cast<float>(i % ray_count) * utils::d2::PIX2 / ray_count;
            const sf::Vector2f ray_pos = centre_pos + radius * utils::d2::rad_to_vec(angle);
            sectors[i + 1] = sf::Vertex(ray_pos, color);
            if (i < ray_count) {
                ray[i * 2] = sf::Vertex(ray_pos, sf::Color::White);
                ray[i * 2 + 1] = sf::Vertex(centre_pos, sf::Color::Black);
            }
        }
        target.draw(sectors);
        target.draw(ray);
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
