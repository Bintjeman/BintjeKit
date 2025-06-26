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
        void initialise() override;
        void update() override;
        [[nodiscard]] const std::vector<std::vector<bool> > &get_grid() const;
        void on_sfml_event(const sf::Event &event) override;
        void new_world();

    private:
        static constexpr unsigned long GRID_WIDTH = 250;
        static constexpr unsigned long GRID_HEIGHT = 250;
        unsigned long count_neighbors(unsigned long x, unsigned long y);

        std::vector<std::vector<bool> > m_grid;
        std::vector<std::vector<bool> > m_next_grid;
    };
} // gol
#endif //GAME_OF_LIFE_HPP
