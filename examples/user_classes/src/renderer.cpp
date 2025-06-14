/*!
 * @author bintjeman
 * @date 13.06.25
 * @name renderer.cpp
 */

#include "renderer.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine.hpp"

namespace usr {
    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::initialise() {

    }

    void Renderer::configure() {
        if (!m_font.openFromFile("resources/fonts/DejaVuSansMono.ttf")) {
            abort();
        }
        resize_views();
    }

    void Renderer::render() {
        if (!m_render_window || !m_engine) return;
        m_render_window->clear();
        m_drawables.clear();
        m_engine_renderer->get_drawable(m_drawables);
        for (const auto &drawable: m_drawables) {
            m_render_window->setView(m_engine_view);
            m_render_window->draw(drawable);
        }
        m_render_window->setView(m_gui_view);
        renderGUI();
        m_render_window->display();
    }

    void Renderer::renderGUI() {
        static sf::Text text_ticks(m_font);
        text_ticks.setCharacterSize(10);
        text_ticks.setFillColor(sf::Color::White);
        text_ticks.setString("Ticks: " + std::to_string(m_usr_engine->ticks()));
        m_render_window->setView(m_gui_view);
        m_render_window->draw(text_ticks);
    }

    void Renderer::set_engine(bnjkit::engine::IEngine *engine) {
        IRenderer::set_engine(engine);
        m_usr_engine = dynamic_cast<const Engine *>(engine);
    }

    void Renderer::set_render_window(sf::RenderWindow *window) {
        IRenderer::set_render_window(window);
    }

    void Renderer::on_sfml_event(const sf::Event &event) {
        if (const auto &resized = event.getIf<sf::Event::Resized>()) {
            resize_views();
        }
    }
} // usr
