/*!
 * @author bintjeman
 * @date 01.07.25
 * @name evobotrenderer.cpp
 */
#include "evobot_renderer.hpp"
#include <spdlog/logger.h>

#include "bintjekit/renderer/i_renderer.hpp"
#include "evobot_engine/evobot_engine.hpp"
#include "evobot_engine/evo_world.hpp"
#include "evobot_engine/components/base_components.hpp"

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
