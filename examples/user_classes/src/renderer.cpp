/*!
 * @author bintjeman
 * @date 13.06.25
 * @name renderer.cpp
 */

#include "renderer.hpp"
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine.hpp"

namespace usr {
    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::initialise() {
    }

    void Renderer::configure() {
    }

    void Renderer::render() {
        if (!m_render_window || !m_engine) return;
        m_render_window->clear();
        m_drawables.clear();
        m_engine_renderer->get_drawable(m_drawables);
        for (const auto &drawable: m_drawables) {
            m_render_window->draw(drawable);
        }
        m_render_window->display();
    }

    void Renderer::renderGUI() {
    }

    void Renderer::set_engine(bnjkit::engine::IEngine *engine) {
        IRenderer::set_engine(engine);
        m_usr_engine = dynamic_cast<const Engine *>(engine);
    }

    void Renderer::set_render_window(sf::RenderWindow *window) {
        IRenderer::set_render_window(window);
    }
} // usr
