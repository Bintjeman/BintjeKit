/*!
 * @author bintjeman
 * @date 23.07.25
 * @name render_back_ground.cpp
 */

#include "render_background.hpp"
#include <spdlog/spdlog.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <bintjekit/configuration/json_adapter.hpp> // sf::Color, sf::Vector2<>
#include <bintjekit/configuration/node.hpp>
#include <bintjekit/engine/i_engine.hpp>
#include <bintjekit/engine/play_ground.hpp>

namespace evo::renderer {
    namespace {
        constexpr auto COLOR_PTR = "/Color";
        constexpr auto OUTLINE_COLOR_PTR = "/Outline color";
    }

    RenderBackGround::RenderBackGround() {
        m_logger->info("Build {}", RenderBackGround::name());
    }
    RenderBackGround::~RenderBackGround() {
        m_logger->info("Destroy {}", RenderBackGround::name());
    }
    void RenderBackGround::initialize(bnjkit::engine::IEngine& engine) {
        m_logger->trace("Initialize {}", RenderBackGround::name());
        m_engine = & engine;
    }
    void RenderBackGround::configure(bnjkit::conf::Node node) {
        m_logger->trace("Configure {}", RenderBackGround::name());
        m_background_color = node.get_or_set(COLOR_PTR, m_background_color);
        m_outline_color = node.get_or_set(OUTLINE_COLOR_PTR, m_outline_color);
    }
    void RenderBackGround::render(sf::RenderTarget& target) const {
        static const auto& playground = m_engine->play_ground();
        static auto quad = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 4);
        static auto outline = sf::VertexArray(sf::PrimitiveType::LineStrip, 5);
        const std::array points{
            playground.position(),
            playground.position() + sf::Vector2f(playground.size().x, 0),
            playground.position() + playground.size(),
            playground.position() + sf::Vector2f(0.f, playground.size().y),
        };
        outline[0] = {points[0], m_outline_color};
        outline[1] = {points[1], m_outline_color};
        outline[2] = {points[2], m_outline_color};
        outline[3] = {points[3], m_outline_color};
        outline[4] = {points[0], m_outline_color};
        quad[0] = {points[0], m_background_color};
        quad[1] = {points[1], m_background_color};
        quad[2] = {points[3], m_background_color};
        quad[3] = {points[2], m_background_color};
        target.draw(quad);
        target.draw(outline);
    }
    std::string RenderBackGround::name() const {
        return "Render BackGround";
    }
}
