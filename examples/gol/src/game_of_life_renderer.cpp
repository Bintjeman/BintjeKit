/*!
 * @author bintjeman
 * @date 14.06.25
 * @name game_of_life_renderer.cpp
 */

#include "../include/game_of_life_renderer.hpp"

namespace gol {
    GameOfLifeRenderer::GameOfLifeRenderer() {
        cell_shape.setSize({CELL_SIZE, CELL_SIZE});
        cell_shape.setFillColor(sf::Color::White);  // ou une autre couleur visible
        cell_shape.setOutlineColor(sf::Color::Black);
        cell_shape.setOutlineThickness(1.0f);

    }

    void GameOfLifeRenderer::get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const {
        const auto &grid = m_gol->getGrid();
        for (size_t y = 0; y < grid.size(); ++y) {
            for (size_t x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x]) {
                    cell_shape.setPosition({x * CELL_SIZE, y * CELL_SIZE});
                    drawable_list.emplace_back(std::ref(cell_shape));
                }
            }
        }
    }

    void GameOfLifeRenderer::set_engine(const bnjkit::engine::IEngine *engine) {
        IEngineRenderer::set_engine(engine);
        m_gol = dynamic_cast<const GameOfLife *>(engine);
    }
} // gol
