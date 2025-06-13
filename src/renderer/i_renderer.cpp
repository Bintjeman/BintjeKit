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

        void IRenderer::render() {
        }

        void IRenderer::renderGUI() {
        }

        void IRenderer::set_engine_renderer(renderer::IEngineRenderer *engine_renderer) {
            m_engine_renderer = engine_renderer;
        }

        void IRenderer::set_render_window(sf::RenderWindow *window) {
            m_render_window = window;
        }

        void IRenderer::set_engine(engine::IEngine *engine) {
            m_engine = engine;
        }
    } // renderer
} // bnjkit
