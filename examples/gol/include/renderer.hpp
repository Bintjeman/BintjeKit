/*!
 * @author bintjeman
 * @date 14.06.25
 * @name renderer.hpp
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once
#include <bintjekit/renderer/i_renderer.hpp>

namespace gol {
    class GameOfLife;
    class Renderer : public bnjkit::renderer::IRenderer {
    public:
        Renderer();
        void on_sfml_event(const sf::Event &event) override;
        void render_gui() override;
        void set_engine(const bnjkit::engine::IEngine *engine) override;

    private:
        const GameOfLife *m_gol;
    };
} // gol

#endif //RENDERER_HPP
