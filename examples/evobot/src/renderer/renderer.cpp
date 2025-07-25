/*!
 * @author bintjeman
 * @date 23.07.25
 * @name renderer.cpp
 */
#include "renderer.hpp"
#include <bintjekit/core/module_set.hpp>

#include "render_evobot.hpp"
#include "renderer/render_background.hpp"

namespace evo::renderer {
    namespace {
        constexpr auto RENDER_BACKGROUND_PTR = "/Background";
        constexpr auto RENDER_EVOBOT_PTR = "/Evobot";
    }

    Renderer::Renderer() {
        m_logger->info("Build {}", name());
    }
    Renderer::~Renderer() {
        m_logger->info("Destroy {}", name());
    }
    void Renderer::configure() {
        m_logger->trace("Configure {}", name());
        auto render_background = std::make_unique<RenderBackGround>();
        render_background->initialize(m_modules->engine());
        render_background->configure(m_settings.create_child(RENDER_BACKGROUND_PTR));
        add_render_system(std::move(render_background), bnjkit::renderer::RenderLayer::BACKGROUND);
        auto evobot_renderer = std::make_unique<EvobotRenderer>();
        evobot_renderer->initialize(m_modules->engine());
        evobot_renderer->configure(m_settings.create_child(RENDER_EVOBOT_PTR));
        add_render_system(std::move(evobot_renderer), bnjkit::renderer::RenderLayer::ENTITIES);
        m_logger->trace("End configure {}", name());
    }
    void Renderer::on_quit() {
        m_logger->info("{} on quit", name());
        m_render_system_manager.clear();
        IRenderer::on_quit();
    }
    std::string Renderer::name() const {
        return "Evobot Renderer";
    }
}
