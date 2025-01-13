/*!
 * @file gol.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <random>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "tools/logger/logger_define.hpp"
export module gol;
import :renderer;
import :map;
import bik.playground;
import bik.settings;
import bik.logger;
namespace gol {
    using Neighbors = std::vector<int>;

    export class GameOfLife : public bik::playground::BasePlayGround {
    public:
        GameOfLife() {
            LOGGER->info("GameOfLife::GameOfLife()");
        }

        void update() override {
            for (int x = 0; x < map_->size.x; x++) {
                for (int y = 0; y < map_->size.y; y++) {
                    bool grow = false;
                    auto neighbors = get_neighbors(sf::Vector2u(x, y));
                    auto &cell = map_->get(x, y);
                    for (auto neighbor: neighbors) {
                        if (cell.first == map_->max_value - 1 && neighbor == 0) {
                            cell.second = true;
                            break;
                        }
                        if (cell.first + 1 == neighbor) {
                            cell.second = true;
                            break;
                        }
                    }
                }
            }
            for (auto &cell: map_->cells) {
                if (cell.second) {
                    if (cell.first < map_->max_value - 1) {
                        cell.first++;
                        cell.second = false;
                    } else {
                        cell.first = 0;
                        cell.second = false;
                    }
                }
            }
        }

        void initialize() override {
            LOGGER->info("GameOfLife::initialize()");
            if (settings_.get_or_set("/Gol/Rules/Autostart"_json_pointer, true)) {
                new_gol();
            }
        }

        sf::Rect<float> boundaries() const override {
            return sf::Rect<float>({0.f, 0.f}, sf::Vector2f(map_->size));
        }

        void prerendering() {
            gol_renderer_.prerendering();
        }

        sf::Drawable &drawable() {
            return gol_renderer_;
        }

        void new_gol() {
            LOGGER->info("GameOfLife::new_gol()");
            map_ = std::make_shared<Map>();
            gol_renderer_.set_map(map_);
            map_->size = settings_.get_or_set("/Gol/Rules/Size"_json_pointer,
                                              sf::Vector2u(100, 100));
            map_->max_value = settings_.get_or_set("/Gol/Rules/MaxValue"_json_pointer, 16);
            map_->cells.clear();
            map_->cells.resize(map_->size.x * map_->size.y);
            generation(*map_);
            gol_renderer_.initialize();
        }

        void kill_gol() {
            LOGGER->info("GameOfLife::kill_gol()");
            map_ = nullptr;
        }

        sf::Vector2u get_size() {
            if (map_ == nullptr) {
                return sf::Vector2u(0, 0);
            } else {
                return map_->size;
            }
        }

    private:
        Neighbors get_neighbors(const sf::Vector2u &pos) {
            std::vector<int> neighbors;
            if (pos.y > 0) {
                neighbors.push_back(map_->get(pos.x, pos.y - 1).first);
            }
            if (pos.y < map_->size.y - 1) {
                neighbors.push_back(map_->get(pos.x, pos.y + 1).first);
            }
            if (pos.x > 0) {
                neighbors.push_back(map_->get(pos.x - 1, pos.y).first);
            }
            if (pos.x < map_->size.x - 1) {
                neighbors.push_back(map_->get(pos.x + 1, pos.y).first);
            }
            return neighbors;
        }

        std::shared_ptr<Map> map_ = nullptr;
        GolRenderer gol_renderer_;

        static void generation(Map &map) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, map.max_value - 1);
            for (auto &cell: map.cells) {
                cell = std::pair(dis(gen), false);
            }
        }
    };
}
