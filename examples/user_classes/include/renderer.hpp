/*!
 * @author bintjeman
 * @date 13.06.25
 * @name renderer.hpp
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include <SFML/Graphics/Font.hpp>
#include "bintjekit/renderer/i_renderer.hpp"

namespace usr {
    class Engine;

    class Renderer : public bnjkit::renderer::IRenderer {
    public:
        Renderer();
        ~Renderer() override;
        void initialise() override;
        void configure() override;
        void render_scene() override;
        void render_gui() override;
        void set_engine(const bnjkit::engine::IEngine *engine) override;
        void set_render_window(sf::RenderWindow *window) override;
        void on_sfml_event(const sf::Event &event) override;

    private:
        sf::Font m_font;
        const Engine *m_usr_engine;
    };
} // usr

#endif //RENDERER_HPP
