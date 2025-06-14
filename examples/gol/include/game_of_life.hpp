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
        const std::vector<std::vector<bool>>& get_grid() const;
    private:
        int count_neighbors(int x, int y);

        static constexpr int GRID_WIDTH = 100;
        static constexpr int GRID_HEIGHT = 100;
        std::vector<std::vector<bool> > m_grid;
        std::vector<std::vector<bool> > m_next_grid;
    };
} // gol
#endif //GAME_OF_LIFE_HPP
