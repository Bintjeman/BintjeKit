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
        // m_circle_shape.setPointCount(32);
    }
    void CircleRenderSystem::render(sf::RenderTarget& target) const {
        auto current_view = view();
        m_logger->debug("View center: ({}, {}), size: ({}, {})",
        current_view.getCenter().x, current_view.getCenter().y,
        current_view.getSize().x, current_view.getSize().y);

        target.setView(current_view);
        // Rendu des bots
        // const auto bot_view = m_registry.view<const engine::comp::D2, const engine::comp::EvobotTag>();
        // bot_view.each([this, &target](const engine::comp::D2& d2,const engine::comp::EvobotTag& tag) {
        //   m_circle_shape.setRadius(d2.radius);
        //     m_circle_shape.setPosition(d2.position - sf::Vector2f(d2.radius, d2.radius));
        //     m_circle_shape.setFillColor(sf::Color(50, 150, 250));
        //     target.draw(m_circle_shape);
        // });
        // Rendu des bots
        sf::CircleShape circle_shape;
        circle_shape.setPointCount(32);

        // const auto bot_view = m_registry.view<const engine::comp::D2, const engine::comp::EvobotTag>();
        // for (const auto entity: bot_view) {
        // const auto& d2 = bot_view.get<const engine::comp::D2>(entity);
        // circle_shape.setRadius(d2.radius);
        // circle_shape.setPosition(d2.position - sf::Vector2f(d2.radius, d2.radius));
        // circle_shape.setFillColor(sf::Color(50, 150, 250));
        // target.draw(circle_shape);
        // }
        // const auto circle_view = m_registry.view<const engine::comp::D2>();
        // circle_view.each([&target, &circle_shape](auto entity, const engine::comp::D2& d2) {
        //     circle_shape.setRadius(d2.radius);
        //     circle_shape.setPosition(d2.position - sf::Vector2f(d2.radius, d2.radius));
        //     circle_shape.setFillColor(sf::Color(50, 150, 250));
        //     target.draw(circle_shape);
        // });
        const auto circle_view = m_registry.view<const engine::comp::D2>();
        m_logger->debug("Number of entities with D2: {}", circle_view.size());
        const auto evobot_view = m_registry.view<const engine::comp::EvobotTag>();
        m_logger->debug("Number of entities with EvobotTag: {}", evobot_view.size());
        const auto bot_view = m_registry.view<engine::comp::D2, engine::comp::EvobotTag>();
        // m_logger->debug("Number of entities with D2 and EvobotTag: {}", bot_view);
        bot_view.each([this,&target, &circle_shape](const auto& d2, const auto& tag) {
            circle_shape.setRadius(d2.radius);
            circle_shape.setPosition(d2.position - sf::Vector2f(d2.radius, d2.radius));
            circle_shape.setFillColor(sf::Color(50, 150, 250));
            m_logger->debug("Drawing circle at: ({}, {}), radius: {}",
                            d2.position.x, d2.position.y, d2.radius);
            target.draw(circle_shape);
        });

        // const auto bot_view = m_registry.view<const engine::comp::D2, const engine::comp::EvobotTag>();
        // bot_view.each(
        //     [&target, &circle_shape](auto entity, const engine::comp::D2& d2, const engine::comp::EvobotTag& tag) {
        //         circle_shape.setRadius(d2.radius);
        //         circle_shape.setPosition(d2.position - sf::Vector2f(d2.radius, d2.radius));
        //         circle_shape.setFillColor(sf::Color(50, 150, 250));
        //         target.draw(circle_shape);
        //     });

        // Rendu des globs
        // auto glob_view = m_registry.view<const engine::comp::D2, const engine::comp::GlobTag>();
        // glob_view.each(
        //     [this, &target](const auto& entity, const engine::comp::D2& d2, const engine::comp::GlobTag& tag) {
        //         m_circle_shape.setRadius(d2.radius);
        //         m_circle_shape.setPosition(d2.position - sf::Vector2f(d2.radius, d2.radius));
        //         m_circle_shape.setFillColor(sf::Color(50, 250, 50));
        //         target.draw(m_circle_shape);
        //     });
    }
    std::string CircleRenderSystem::name() const {
        return "CircleRenderSystem";
    }
}
