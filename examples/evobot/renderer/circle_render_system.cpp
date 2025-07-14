/*!
 * @author bintjeman
 * @date 13.07.25
 * @name circle_render_system.cpp
 */
#include "circle_render_system.hpp"
#include <spdlog/logger.h>
#include <entt/entity/registry.hpp>
#include <entt/entt.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "evobot_engine/components/base_components.hpp"

namespace evo::renderer {
    CircleRenderSystem::~CircleRenderSystem() = default;
    CircleRenderSystem::CircleRenderSystem(const entt::registry& registry)
        : m_registry(registry) {
    }
    void CircleRenderSystem::render(sf::RenderTarget& target) const {
        // Rendu des bots
        sf::CircleShape circle_shape;
        circle_shape.setPointCount(32);
        const auto bot_view = m_registry.view<engine::comp::D2, engine::comp::EvobotTag>();
        bot_view.each([this,&target, &circle_shape](const auto& d2, const auto& tag) {
            circle_shape.setRadius(d2.radius);
            circle_shape.setPosition(d2.position - sf::Vector2f(d2.radius, d2.radius));
            circle_shape.setFillColor(sf::Color(50, 150, 250,200));
            target.draw(circle_shape);
        });
        const auto glob_view = m_registry.view<engine::comp::D2, engine::comp::GlobTag>();
        glob_view.each([this,&target, &circle_shape](const auto& d2, const auto& tag) {
            circle_shape.setRadius(d2.radius);
            circle_shape.setPosition(d2.position - sf::Vector2f(d2.radius, d2.radius));
            circle_shape.setFillColor(sf::Color(50, 255, 250,200));
            target.draw(circle_shape);
        });
    }
    std::string CircleRenderSystem::name() const {
        return "CircleRenderSystem";
    }
}
