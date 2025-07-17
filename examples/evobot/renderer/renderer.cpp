/*!
 * @author bintjeman
 * @date 01.07.25
 * @name renderer.cpp
 */

#include "renderer.hpp"
#include <spdlog/logger.h>

#include "evobot_engine/evobot_engine.hpp"

namespace evo::renderer {
    void Renderer::configure() {
        m_logger->info("Renderer: configuring");
        IRenderer::configure();
        m_render_system_manager.set_default_view(m_world_view, true);
    }
    std::string Renderer::name() const {
        return "Renderer";
    }
    void Renderer::camera_move(const sf::Vector2f delta) {
        m_world_view->move(delta);
    }
    void Renderer::camera_zoom(const float ratio) {
        m_world_view->zoom(ratio);
    }
    void Renderer::set_engine(const bnjkit::engine::IEngine* engine) {
        IRenderer::set_engine(engine);
        m_evobot = dynamic_cast<const engine::EvobotEngine*>(engine);
    }
}
