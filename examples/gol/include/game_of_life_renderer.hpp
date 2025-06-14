/*!
 * @author bintjeman
 * @date 14.06.25
 * @name game_of_life_renderer.hpp
 */

#ifndef GAME_OF_LIFE_RENDERER_HPP
#define GAME_OF_LIFE_RENDERER_HPP
#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <bintjekit/renderer/i_engine_renderer.hpp>

#include "game_of_life.hpp"

namespace gol {
    class GameOfLifeRenderer : public bnjkit::renderer::IEngineRenderer {
    public:
        GameOfLifeRenderer();
        void get_drawable(std::vector<std::reference_wrapper<sf::Drawable>> &drawable_list) const override;
        void set_engine(const bnjkit::engine::IEngine *engine) override;

    private:
        static constexpr float CELL_SIZE = 1.0f;
        const GameOfLife* m_gol;
        mutable sf::RectangleShape cell_shape;
    };


} // gol

#endif //GAME_OF_LIFE_RENDERER_HPP
