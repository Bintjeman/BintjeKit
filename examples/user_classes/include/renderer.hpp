/*!
 * @author bintjeman
 * @date 13.06.25
 * @name renderer.hpp
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "bintjekit/renderer/i_renderer.hpp"

namespace usr {
    class Engine;

    class Renderer : public bnjkit::renderer::IRenderer {
    public:
        Renderer();
        ~Renderer() override;
        void initialise() override;
        void configure() override;
        void render() override;
        void renderGUI() override;
        void set_engine(bnjkit::engine::IEngine *engine) override;
        void set_render_window(sf::RenderWindow *window) override;
    private:
        sf::View m_egnine_view;
        sf::View m_gui_view;
        const Engine *m_usr_engine;
    };
} // usr

#endif //RENDERER_HPP
