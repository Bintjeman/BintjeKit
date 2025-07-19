/*!
 * @author bintjeman
 * @date 19.07.25
 * @name ball_renderer.cpp
 */

#include "ball_renderer.hpp"
#include <spdlog/spdlog.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "engine/billard.hpp"
#include "engine/components/entity.hpp"
#include "engine/components/position_component.hpp"
#include "engine/components/radius_component.hpp"

namespace bil {
    BallRenderer::~BallRenderer() {
        m_logger->info("BallRenderer destroyed");
    }
    void BallRenderer::initialize(bnjkit::engine::IEngine& engine) {
        m_billard = dynamic_cast<Billard*>(& engine);
    }
    void BallRenderer::render(sf::RenderTarget& target) const {
        sf::CircleShape ball_circle;
        ball_circle.setFillColor(sf::Color::Red);
        static auto& registry = m_billard->registry();
        const auto ball_view = registry.view<components::PositionComponent, components::RadiusComponent,
            components::BallFlag>();
        ball_view.each([ &target, &ball_circle](auto& position, auto& radius) {
            ball_circle.setPosition({position.position.x - radius.radius, position.position.y - radius.radius});
            ball_circle.setRadius(radius.radius);
            target.draw(ball_circle);
        });
    }
    std::string BallRenderer::name() const {
        return "Ball renderer";
    }
} // bil
