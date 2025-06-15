/*!
 * @author bintjeman
 * @date 14.06.25
 * @name game_of_life.cpp
 */

#include "game_of_life.hpp"
#include <spdlog/logger.h>
#include "bintjekit/engine/play_ground.hpp"

namespace gol {
    GameOfLife::GameOfLife(): IEngine() {
    }
    void GameOfLife::initialise() {
        m_play_ground->size = {GRID_WIDTH, GRID_HEIGHT};
        m_grid.resize(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));
        m_next_grid.resize(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));
    }
    void GameOfLife::update() {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                const int neighbors = count_neighbors(x, y);
                const bool current_cell = m_grid[y][x];
                if (current_cell && (neighbors < 2 || neighbors > 3)) {
                    m_next_grid[y][x] = false;
                } else if (!current_cell && neighbors == 3) {
                    m_next_grid[y][x] = true;
                } else {
                    m_next_grid[y][x] = current_cell;
                }
            }
        }
        std::swap(m_grid, m_next_grid);
    }

    const std::vector<std::vector<bool> > &GameOfLife::get_grid() const {
        return m_grid;
    }

    int GameOfLife::count_neighbors(int x, int y) {
        int count = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;
                int nx = (x + dx + GRID_WIDTH) % GRID_WIDTH;
                int ny = (y + dy + GRID_HEIGHT) % GRID_HEIGHT;
                if (m_grid[ny][nx]) count++;
            }
        }
        return count;
    }



    void GameOfLife::on_sfml_event(const sf::Event &event) {
        auto shift = []() {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift) || sf::Keyboard::isKeyPressed(
                    sf::Keyboard::Key::LShift)) {
                return true;
            }
            return false;
        };
        if (const auto &key = event.getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::N) {
                if (shift()) {
                    new_world();
                }
            }
        }
    }

    void GameOfLife::new_world() {
        m_logger->info("New world");
        m_play_ground->size = {GRID_WIDTH, GRID_HEIGHT};
        m_grid.resize(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));
        m_next_grid.resize(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                m_grid[y][x] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) > 0.5f;
                m_next_grid[y][x] = m_grid[y][x];
            }
        }
        m_state = READY;
    }
} // gol
