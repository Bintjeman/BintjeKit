/*!
 * @author bintjeman
 * @date 13.06.25
 * @name renderer.cpp
 */

#include "renderer.hpp"

namespace usr {
    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::initialise() {
    }

    void Renderer::configure() {
    }

    void Renderer::render() {
        m_render_window->clear();
        if (!m_render_window || !m_engine) return;
        m_render_window->clear();
        m_drawables.clear();
        m_engine->get_drawable(m_drawables);
        for (const auto &drawable: m_drawables) {
            m_render_window->draw(drawable);
        }
        m_render_window->display();
    }

    void Renderer::renderGUI() {
    }
} // usr
