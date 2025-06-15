/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.cpp
 */

#include "bintjekit/renderer/i_renderer.hpp"

#include <imgui-SFML.h>
#include "fmt_sfml/fmt_sfml.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"
#include "bintjekit/renderer/i_bnjkit_imgui.hpp"

namespace bnjkit {
    namespace renderer {
        IRenderer::IRenderer() : m_engine(nullptr), m_render_window(nullptr) {
            m_logger = core::Logger::get_logger(core::module_names::RENDERER);
            m_logger->set_level(spdlog::level::trace);
            m_logger->info("Constructor of IRenderer");
        }

        IRenderer::~IRenderer() {
            m_logger->info("Destructor of IRenderer");
        }

        void IRenderer::configure() {
            m_logger->info("Configuring IRenderer");
            resize_views();
        }

        void IRenderer::render() {
            if (!m_render_window || !m_engine) return;
            begin_frame();
            render_scene();
            render_gui();
            end_frame();
        }

        void IRenderer::render_scene() {
            m_drawables.clear();
            m_engine_renderer->get_drawable(m_drawables);
            for (const auto &drawable: m_drawables) {
                m_render_window->setView(m_engine_view);
                m_render_window->draw(drawable);
            }
        }

        void IRenderer::render_gui() {
            m_render_window->setView(m_gui_view);
        }

        void IRenderer::set_engine_renderer(renderer::IEngineRenderer *engine_renderer) {
            m_logger->info("Setting engine renderer");
            m_engine_renderer = engine_renderer;
        }

        void IRenderer::set_imgui_renderer(IImGuiRenderer *imgui_renderer) {
            m_logger->info("Setting imgui renderer");
            m_imgui_renderer = imgui_renderer;
        }

        void IRenderer::resize_views() {
            m_logger->info("Resizing views");
            const sf::Rect<float> world_bounds = m_engine_renderer->get_bounds();
            const float window_ratio = static_cast<float>(m_render_window->getSize().x) / static_cast<float>(
                                           m_render_window->getSize().y);
            const float world_ratio = world_bounds.size.x / world_bounds.size.y;
            m_gui_view = m_render_window->getDefaultView();
            m_engine_view.setCenter({
                world_bounds.position.x + world_bounds.size.x / 2.0f,
                world_bounds.position.y + world_bounds.size.y / 2.0f
            });
            if (window_ratio > world_ratio) {
                // La fenêtre est plus large que le monde
                float view_height = world_bounds.size.y;
                float view_width = view_height * window_ratio;
                m_engine_view.setSize({view_width, view_height});
            } else {
                // La fenêtre est plus haute que le monde
                float view_width = world_bounds.size.x;
                float view_height = view_width / window_ratio;
                m_engine_view.setSize({view_width, view_height});
            }
            m_logger->trace("Engine bounds: {}\nwindow size: {}\nView center: {}\nView size: {}",
                            m_engine_renderer->get_bounds(), m_render_window->getSize(), m_engine_view.getCenter(),
                            m_engine_view.getSize());
        }

        void IRenderer::begin_frame() {
            m_render_window->clear();
        }

        void IRenderer::end_frame() {
            m_imgui_renderer->render();
            m_render_window->display();
        }

        void IRenderer::set_render_window(sf::RenderWindow *window) {
            m_logger->info("Setting render window");
            m_render_window = window;
            m_engine_view = window->getDefaultView();
            m_gui_view = window->getDefaultView();
        }

        void IRenderer::set_engine(engine::IEngine *engine) {
            m_logger->info("Setting engine");
            m_engine = engine;
        }
    } // renderer
} // bnjkit
