/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.cpp
 */

#include "bintjekit/renderer/i_renderer.hpp"

#include <imgui-SFML.h>
#include "bintjekit/utils/fmt_sfml/fmt_sfml.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/engine/play_ground.hpp"
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/renderer/i_bnjkit_imgui.hpp"
#include "bintjekit/renderer/i_render_system.hpp"
#include "bintjekit/window/i_main_window.hpp"

namespace bnjkit::renderer {
    IRenderer::IRenderer(): m_render_window(nullptr), m_imgui_renderer(nullptr), m_core(nullptr), m_engine(nullptr) {
        m_logger = core::Logger::get_logger(literals::logger::RENDERER);
        m_logger->info("IRenderer: Constructor of IRenderer");
        m_world_view = std::make_shared<sf::View>();
        m_gui_view = std::make_shared<sf::View>();
    }

    IRenderer::~IRenderer() {
        m_logger->info("IRenderer: Destructor of IRenderer");
    }

    void IRenderer::configure() {
        m_logger->trace("IRenderer: Configuring IRenderer");
        resize_views();
    }

    void IRenderer::render() {
        if (!m_render_window || !m_engine) {
            m_logger->warn("Render skipped: m_render_window={}, m_engine={}",
                           static_cast<const void*>(m_render_window),
                           static_cast<const void*>(m_engine));
            return;
        }
        begin_frame();
        render_scene();
        render_gui();
        end_frame();
    }
    void IRenderer::resize_views() {
        m_logger->trace("IRenderer: Resizing views");
        const auto& bounds = m_engine->play_ground().bounds();
        const sf::Rect<float> world_bounds = bounds;
        const float window_ratio = static_cast<float>(m_render_window->getSize().x) /
                                   static_cast<float>(
                                       m_render_window->getSize().y);
        const float world_ratio = world_bounds.size.x / world_bounds.size.y;
        * m_gui_view = m_render_window->getDefaultView();
        m_world_view->setCenter({
            world_bounds.position.x + (world_bounds.size.x / 2.0f),
            world_bounds.position.y + (world_bounds.size.y / 2.0f)
        });
        if (window_ratio > world_ratio) {
            // La fenêtre est plus large que le monde
            float view_height = world_bounds.size.y;
            float view_width = view_height * window_ratio;
            m_world_view->setSize({view_width, view_height});
        } else {
            // La fenêtre est plus haute que le monde
            float view_width = world_bounds.size.x;
            float view_height = view_width / window_ratio;
            m_world_view->setSize({view_width, view_height});
        }
        m_logger->trace(
            "IRenderer: Engine bounds: {}\nwindow size: {}\nView center: {}\nView size: {}",
            bounds, m_render_window->getSize(),
            m_world_view->getCenter(),
            m_world_view->getSize());
    }
    void IRenderer::add_render_system(std::unique_ptr<IRenderSystem> system, RenderLayer layer) {
        m_logger->trace("IRenderer: Adding render system: {} at layer: {}", system->name(), layer);
        m_render_system_manager.add_system(std::move(system), layer);
    }
    void IRenderer::remove_render_system(const std::string& name) {
        m_logger->trace("IRenderer: Removing render system: {}", name);
        m_render_system_manager.remove_system(name);
    }
    void IRenderer::toggle_render_system(const std::string& name, bool enable) {
        m_logger->trace("IRenderer: Toggling render system: {} to {}", name, enable);
        m_render_system_manager.toggle_system(name, enable);
    }
    void IRenderer::render_scene() {
        m_render_system_manager.render(*m_render_window);
    }
    void IRenderer::render_gui() {
        m_render_window->setView(* m_gui_view);
        m_imgui_renderer->draw();
    }
    void IRenderer::set_render_window(sf::RenderWindow* window) {
        m_logger->trace("IRenderer: Setting render window");
        m_render_window = window;
        * m_world_view = window->getDefaultView();
        * m_gui_view = window->getDefaultView();
    }
    void IRenderer::set_imgui_renderer(IImGuiRenderer* imgui_renderer) {
        m_logger->trace("IRenderer: Setting imgui renderer");
        m_imgui_renderer = imgui_renderer;
    }
    void IRenderer::set_core(core::Core* core) {
        m_logger->trace("IRenderer: Setting core");
        m_core = core;
    }
    void IRenderer::set_engine(const engine::IEngine* world) {
        m_logger->trace("IRenderer: Setting engine");
        m_engine = world;
    }

    void IRenderer::begin_frame() const {
        m_render_window->clear();
    }

    void IRenderer::end_frame() const {
        m_imgui_renderer->render();
        m_render_window->display();
    }
    std::string IRenderer::name() const {
        return "IRenderer";
    }
}
