/*!
 * @author bintjeman
 * @date 14.06.25
 * @name game_of_life.cpp
 */

#include "../include/game_of_life.hpp"

#include "bintjekit/engine/play_ground.hpp"

namespace gol {
    GameOfLife::GameOfLife() {
        // Initialisation des grilles
        m_play_ground->size={GRID_WIDTH, GRID_HEIGHT};
        grid.resize(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));
        nextGrid.resize(GRID_HEIGHT, std::vector<bool>(GRID_WIDTH, false));

        // Configuration initiale (glider pattern)
        grid[1][2] = true;
        grid[2][3] = true;
        grid[3][1] = true;
        grid[3][2] = true;
        grid[3][3] = true;
    }

    void GameOfLife::update() {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                int neighbors = count_neighbors(x, y);
                bool currentCell = grid[y][x];

                // Règles du Game of Life
                if (currentCell && (neighbors < 2 || neighbors > 3)) {
                    nextGrid[y][x] = false;
                } else if (!currentCell && neighbors == 3) {
                    nextGrid[y][x] = true;
                } else {
                    nextGrid[y][x] = currentCell;
                }
            }
        }

        // Mise à jour de la grille
        std::swap(grid, nextGrid);
    }

    const std::vector<std::vector<bool> > &GameOfLife::getGrid() const {
        return grid;
    }

    int GameOfLife::count_neighbors(int x, int y) {
        int count = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;
                int nx = (x + dx + GRID_WIDTH) % GRID_WIDTH;
                int ny = (y + dy + GRID_HEIGHT) % GRID_HEIGHT;
                if (grid[ny][nx]) count++;
            }
        }
        return count;
    }
} // gol
