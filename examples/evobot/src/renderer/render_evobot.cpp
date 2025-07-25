/*!
 * @author bintjeman
 * @date 24.07.25
 * @name render_evobot.cpp
 */

#include "render_evobot.hpp"
#include <spdlog/spdlog.h>
#include <entt/entt.hpp>
// SFML
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
// Bintjekit
#include <bintjekit/utils/fmt_sfml/fmt_sfml.hpp>
#include <bintjekit/configuration/json_adapter.hpp>
#include <bintjekit/configuration/node.hpp>
#include <bintjekit/engine/i_engine.hpp>
// Components
#include <bintjekit/utils/d2/d2.hpp>

#include "engine/components/position_comp.hpp"
#include "engine/components/radius_comp.hpp"
#include "engine/components/tag.hpp"

namespace evo::renderer {
    namespace {
        constexpr auto COLOR_PTR = "/Color";
        constexpr auto OUTLINE_COLOR_PTR = "/Outline color";
        constexpr unsigned int CIRCLE_POINTS = 32;
    }

    EvobotRenderer::EvobotRenderer() :IRenderSystem() {
        m_logger->info("Build {}", name());
    }
    EvobotRenderer::~EvobotRenderer() {
        m_logger->info("Destroy {}", name());
    }
    void EvobotRenderer::initialize(bnjkit::engine::IEngine& engine) {
        m_logger->trace("Initialize {}", name());
        m_engine = & engine;
    }
    void EvobotRenderer::configure(bnjkit::conf::Node settings) {
        m_logger->trace("Configure {}", name());
        m_evobot_color = settings.get_or_set(COLOR_PTR, m_evobot_color);
        m_outline_color = settings.get_or_set(OUTLINE_COLOR_PTR, m_outline_color);
    }
    void EvobotRenderer::render(sf::RenderTarget& target) const {
        m_logger->trace("Render {}", name());
        if (!m_engine) {
            m_logger->error("Engine is null in {}", name());
            return;
        }
        constexpr float PIF = bnjkit::utils::d2::PIX2;
        auto& registry = m_engine->registry();
        auto circle = sf::VertexArray(sf::PrimitiveType::TriangleFan, CIRCLE_POINTS + 2);
        auto outline = sf::VertexArray(sf::PrimitiveType::LineStrip, CIRCLE_POINTS + 1);
        const auto view = registry.view<engine::comp::RadiusComp, engine::comp::PositionComp,
            engine::comp::EvobotTag>();
        m_logger->trace("Entity loop:");
        for (const auto entity: view) {
            const auto& [radius] = view.get<engine::comp::RadiusComp>(entity);
            const auto& [position] = view.get<engine::comp::PositionComp>(entity);
            circle[0] = {position, m_evobot_color};
            sf::Vector2f first_point;
            for (unsigned int i = 1; i <= CIRCLE_POINTS; ++ i) {
                static constexpr auto CIRCLE_POINTS_F = static_cast<float>(CIRCLE_POINTS);
                const auto point = sf::Vector2f(radius * std::cos(PIF * static_cast<float>(i) / CIRCLE_POINTS_F),
                                                radius * std::sin(PIF * static_cast<float>(i) / CIRCLE_POINTS_F));
                if (i == 1) { first_point = point; }
                circle[i] = {position + point, m_evobot_color};
                outline[i - 1] = {position + point, m_outline_color};
            }
            outline[CIRCLE_POINTS] = {position + first_point, m_outline_color};
            circle[CIRCLE_POINTS + 1] = {position, m_evobot_color};
            m_logger->trace("Entity : radius: {}, position: {}", radius, position);
            target.draw(circle);
            target.draw(outline);
        }
        m_logger->trace("End render {}", name());
    }
    std::string EvobotRenderer::name() const {
        return "Evobot Renderer";
    }
}
