/*!
 * @file map.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <vector>
#include <SFML/System/Vector2.hpp>
export module gol:map;
namespace gol {
    export class Map {
    public:
        using cell = std::pair<int,bool>;
        cell &get(sf::Vector2i pos) { return get(pos.x, pos.y); }
        cell &get(int x, int y) { return cells[x + y * size.x]; }
        [[nodiscard]] long coord_to_index(sf::Vector2i pos) const { return pos.x + pos.y * size.x; }
        [[nodiscard]] long coord_to_index(int x, int y) const { return x + y * size.x; }
        [[nodiscard]] sf::Vector2i index_to_coord(long i) const {
            int x = i % size.x;
            int y = i / size.x;
            return {x, y};
        }
        sf::Vector2u size;
        unsigned int max_value = 16;
        std::vector<cell> cells;
    };
}
