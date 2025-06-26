/*!
 * @author bintjeman
 * @date 14.06.25
 * @name game_of_life_renderer.cpp
 */
#include "game_of_life_renderer.hpp"
#include "bintjekit/engine/play_ground.hpp"

namespace gol {
    GameOfLifeRenderer::GameOfLifeRenderer(): IEngineRenderer() {
        cell_shape.setSize({CELL_SIZE, CELL_SIZE});
        cell_shape.setFillColor(sf::Color::White); // ou une autre couleur visible
        cell_shape.setOutlineColor(sf::Color::Black);
        cell_shape.setOutlineThickness(0.5f);
    }
    void GameOfLifeRenderer::get_drawable(
        std::vector<std::reference_wrapper<sf::Drawable> >& drawable_list) const {
        const auto& grid = m_gol->get_grid();
        static sf::RectangleShape background;
        m_cells.clear();
        m_cells.reserve(grid.size() * grid[0].size());
        background.setSize(get_bounds().size);
        background.setFillColor(sf::Color::Green);
        drawable_list.emplace_back(std::ref(background));
        int cellules_vivantes [[maybe_unused]] = 0;
        for (size_t y = 0; y < grid.size(); ++ y) {
            for (size_t x = 0; x < grid[y].size(); ++ x) {
                if (grid[y][x]) {
                    cellules_vivantes++;
                    m_cells.emplace_back(cell_shape);
                    m_cells.back().setPosition({
                        static_cast<float>(x) * CELL_SIZE, static_cast<float>(y) * CELL_SIZE
                    });
                    drawable_list.emplace_back(std::ref(m_cells.back()));
                }
            }
        }
    }
    void GameOfLifeRenderer::set_engine(const bnjkit::engine::IEngine* engine) {
        IEngineRenderer::set_engine(engine);
        m_gol = dynamic_cast<const GameOfLife*>(engine);
    }
    sf::Rect<float> GameOfLifeRenderer::get_bounds() const {
        return {
            {0.f, 0.f},
            {m_engine->play_ground().size.x * CELL_SIZE, m_engine->play_ground().size.y * CELL_SIZE}
        };
    }
} // gol
