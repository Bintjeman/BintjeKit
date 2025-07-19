/*!
 * @author bintjeman
 * @date 19.07.25
 * @name renderer.cpp
 */

#include "renderer.hpp"
#include "background_renderer.hpp"
#include "bintjekit/core/module_set.hpp"

namespace bil {
    Renderer::Renderer() :DefaultRenderer(){
        m_logger->info("BillardRenderer created");
    }
    Renderer::~Renderer() {
        m_logger->info("BillardRenderer destroyed");
    }
    void Renderer::initialise() {
        bnjkit::renderer::IRenderer::initialise();
    }
    void Renderer::configure() {
        auto background_renderer = std::make_unique<BackgroundRenderer>();
        background_renderer->initialize(m_modules->engine());
        add_render_system(std::move(background_renderer), bnjkit::renderer::RenderPriority::BACKGROUND);
    }
    std::string Renderer::name() const {
        return "BillardRenderer";
    }
} // bil