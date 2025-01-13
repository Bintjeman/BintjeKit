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
    using Neighbors = std::array<int, 8>;
    export class GameOfLife : public bik::playground::BasePlayGround {
    public:
        GameOfLife() {
            LOGGER->info("GameOfLife::GameOfLife()");
        }

        void update() override {
            for (auto &cell: map_->cells) {

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
            map_->size = settings_.get_or_set("/Gol/Rules/Size"_json_pointer, sf::Vector2u(100, 100));
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
            if (pos.x == 0) {
                if (pos.y == 0) {

                }
            }

        }

        std::shared_ptr<Map> map_ = nullptr;
        GolRenderer gol_renderer_;
        static void generation(Map &map) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, map.max_value - 1);
            for (auto &cell: map.cells) {
                cell = dis(gen);
            }
        }
    };
}
