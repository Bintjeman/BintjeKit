/*!
 * @author bintjeman
 * @date 01.07.25
 * @name evobotrenderer.cpp
 */
#include "evobot_renderer.hpp"
#include <spdlog/logger.h>
#include <SFML/Graphics/View.hpp>
#include "evobot_engine/evobot_engine.hpp"
#include "evobot_engine/evo_world.hpp"
#include "evobot_engine/components/base_components.hpp"
#include "circle_render_system.hpp"

namespace evo::renderer {
    EvobotRenderer::EvobotRenderer(): m_evobot_engine(nullptr) {
        m_logger->info("EvobotRenderer: created");
    }

    EvobotRenderer::~EvobotRenderer() {
        m_logger->info("EvobotRenderer: destroyed");
    }
    void EvobotRenderer::set_engine(const bnjkit::engine::IEngine* engine) {
        IEngineRenderer::set_engine(engine);
        m_evobot_engine = dynamic_cast<const engine::EvobotEngine*>(engine);
    }
    void EvobotRenderer::configure() {
        IEngineRenderer::configure();
        m_logger->info("EvobotRenderer: configuring");
        auto* evobot_engine = static_cast<const engine::EvobotEngine*>(m_engine);
        if (!evobot_engine) {
            m_logger->error("Cannot configure renderer: invalid engine");
            return;
        }
        if (!evobot_engine->world()) {
            m_logger->error("Cannot configure renderer: invalid world");
            return;
        }
        m_logger->debug("Creating CircleRenderSystem");
        auto circle_system = std::make_unique<CircleRenderSystem>(
            evobot_engine->world()->registry()
        );
        m_logger->debug("Adding CircleRenderSystem to layer Entities");
        add_render_system(std::move(circle_system),
                          bnjkit::renderer::RenderLayer::ENTITIES);
    }
    sf::Rect<float> EvobotRenderer::bounds() const {
        if ((m_evobot_engine == nullptr) || (m_evobot_engine->world() == nullptr)) {
            return {{0.f, 0.f}, {100.f, 100.f}};
        }
        const auto& playground = m_evobot_engine->world()->play_ground();
        return playground.bounds();
    }

    std::string EvobotRenderer::name() const {
        return "EvobotRenderer";
    }
}
