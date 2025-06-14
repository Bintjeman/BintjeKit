/*!
 * @author bintjeman
 * @date 14.06.25
 * @name game_of_life.hpp
 */
#ifndef GAME_OF_LIFE_HPP
#define GAME_OF_LIFE_HPP
#pragma once
#include <vector>
#include <bintjekit/engine/i_engine.hpp>

namespace gol {
    class GameOfLife : public bnjkit::engine::IEngine {
        public:
        GameOfLife();
        void update() override;
        const std::vector<std::vector<bool>>& getGrid() const;
    private:
        int count_neighbors(int x, int y);

        static constexpr int GRID_WIDTH = 50;
        static constexpr int GRID_HEIGHT = 50;
        std::vector<std::vector<bool> > grid;
        std::vector<std::vector<bool> > nextGrid;
    };
} // gol
#endif //GAME_OF_LIFE_HPP
