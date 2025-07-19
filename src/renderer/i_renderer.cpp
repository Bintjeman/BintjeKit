/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.cpp
 */

#include "bintjekit/renderer/i_renderer.hpp"
#include <imgui-SFML.h>
#include "bintjekit/utils/fmt_sfml/fmt_sfml.hpp"
#include "bintjekit/logger.hpp"
#include "bintjekit/core/module_set.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/engine/play_ground.hpp"
#include "bintjekit/renderer/i_imgui_renderer.hpp"
#include "bintjekit/renderer/i_render_system.hpp"
#include "bintjekit/window/i_main_window.hpp"

namespace bnjkit::renderer {
    IRenderer::IRenderer(): m_modules(nullptr) {
        m_logger = logger::Logger::get_logger(literals::logger::RENDERER);
        m_logger->info("IRenderer: Constructor of IRenderer");
        m_world_view = std::make_shared<sf::View>();
        m_gui_view = std::make_shared<sf::View>();
    }
    IRenderer::~IRenderer() {
        m_logger->info("IRenderer: Destructor of IRenderer");
    }
    void IRenderer::initialise() {
        m_logger->trace("IRenderer: Initialising IRenderer");
        IModule::initialise();
        m_render_system_manager.initialise();
        const auto& window = dynamic_cast<sf::RenderWindow&>(m_modules->window());
        auto& default_view = window.getDefaultView();
        m_world_view = std::make_shared<sf::View>(default_view);
        m_gui_view = std::make_shared<sf::View>(default_view);
        m_render_system_manager.set_default_view(m_world_view, true);
    }
    void IRenderer::configure() {
        m_logger->trace("IRenderer: Configuring IRenderer");
        resize_views();
    }
    void IRenderer::set_modules(core::ModuleSet* modules) {
        m_logger->trace("IRenderer: Setting modules");
        m_modules = modules;
    }
    void IRenderer::render() {
        begin_frame();
        render_scene();
        render_gui();
        end_frame();
    }
    void IRenderer::resize_views() {
        static auto& engine = m_modules->engine();
        static auto& window = m_modules->window();
        m_logger->trace("IRenderer: Resizing views");
        const auto& bounds = engine.play_ground().bounds();
        const sf::Rect<float> world_bounds = bounds;
        const float window_ratio = static_cast<float>(window.getSize().x) /
                                   static_cast<float>(
                                       window.getSize().y);
        const float world_ratio = world_bounds.size.x / world_bounds.size.y;
        * m_gui_view = window.getDefaultView();
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
            bounds, window.getSize(),
            m_world_view->getCenter(),
            m_world_view->getSize());
    }
    void IRenderer::add_render_system(std::unique_ptr<IRenderSystem> system, RenderLayer layer) {
        m_logger->trace("IRenderer: Adding render system: {} at layer: {}", system->name(),
                        std::to_string(static_cast<int>(layer)));
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
        static auto& window = m_modules->window();
        m_render_system_manager.render(window);
    }
    void IRenderer::render_gui() {
        static auto& window = m_modules->window();
        static auto& imgui_renderer = m_modules->imgui_renderer();
        window.setView(* m_gui_view);
        imgui_renderer.draw();
    }
    void IRenderer::begin_frame() const {
        static auto& window = m_modules->window();
        window.clear();
    }
    void IRenderer::end_frame() const {
        static auto& window = m_modules->window();
        static auto& imgui_renderer = m_modules->imgui_renderer();
        imgui_renderer.render();
        window.display();
    }
    std::string IRenderer::name() const {
        return "IRenderer";
    }
    sf::View& IRenderer::engine_view() {
        return * m_world_view;
    }
    const sf::View& IRenderer::engine_view() const {
        return * m_world_view;
    }
}
