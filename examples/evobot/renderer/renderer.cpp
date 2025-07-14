/*!
 * @author bintjeman
 * @date 01.07.25
 * @name renderer.cpp
 */

#include "renderer.hpp"
#include <spdlog/logger.h>

#include "bintjekit/renderer/i_engine_renderer.hpp"
#include "evobot_engine/evobot_engine.hpp"

namespace evo::renderer {

    void Renderer::configure() {
        IRenderer::configure();
        m_engine_renderer->set_default_view(m_engine_view);
        m_engine_renderer->set_view(bnjkit::renderer::RenderLayer::ENTITIES, m_engine_view);
    }
    std::string Renderer::name() const {
        return "Renderer";
    }
    void Renderer::camera_move(const sf::Vector2f delta) {
        m_engine_view->move(delta);
    }
    void Renderer::camera_zoom(const float ratio) {
        m_engine_view->zoom(ratio);
    }
    void Renderer::set_engine(const bnjkit::engine::IEngine* engine) {
        IRenderer::set_engine(engine);
        m_evobot = dynamic_cast<const engine::EvobotEngine*>(engine);
    }
}
