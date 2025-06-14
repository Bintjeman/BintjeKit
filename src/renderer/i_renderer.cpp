/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.cpp
 */

#include "bintjekit/renderer/i_renderer.hpp"

namespace bnjkit {
    namespace renderer {
        IRenderer::IRenderer() : m_engine(nullptr), m_render_window(nullptr) {
        }

        IRenderer::~IRenderer() = default;

        void IRenderer::configure() {
            resize_views();
        }

        void IRenderer::render() {
        }

        void IRenderer::renderGUI() {
        }

        void IRenderer::set_engine_renderer(renderer::IEngineRenderer *engine_renderer) {
            m_engine_renderer = engine_renderer;
        }

        void IRenderer::resize_views() {
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
        }

        void IRenderer::set_render_window(sf::RenderWindow *window) {
            m_render_window = window;
            m_engine_view = window->getDefaultView();
            m_gui_view = window->getDefaultView();
        }

        void IRenderer::set_engine(engine::IEngine *engine) {
            m_engine = engine;
        }
    } // renderer
} // bnjkit
