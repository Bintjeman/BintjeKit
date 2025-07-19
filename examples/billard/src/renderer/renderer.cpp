/*!
 * @author bintjeman
 * @date 19.07.25
 * @name renderer.cpp
 */

#include "renderer.hpp"
#include <bintjekit/core/module_set.hpp>
#include "background_renderer.hpp"
#include "ball_renderer.hpp"

namespace bil {
    Renderer::Renderer() :DefaultRenderer(){
        m_logger->info("BillardRenderer created");
    }
    Renderer::~Renderer() {
        m_logger->info("BillardRenderer destroyed");
    }
    void Renderer::initialise() {
        bnjkit::renderer::IRenderer::initialise();
        m_render_system_manager.set_default_view(m_world_view, true);
    }
    void Renderer::configure() {
        auto background_renderer = std::make_unique<BackgroundRenderer>();
        background_renderer->initialize(m_modules->engine());
        add_render_system(std::move(background_renderer), bnjkit::renderer::RenderPriority::BACKGROUND);
        auto ball_renderer = std::make_unique<BallRenderer>();
        ball_renderer->initialize(m_modules->engine());
        add_render_system(std::move(ball_renderer), bnjkit::renderer::RenderPriority::ENTITIES);
    }
    std::string Renderer::name() const {
        return "BillardRenderer";
    }
} // bil