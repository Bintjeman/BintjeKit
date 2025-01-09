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
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/fmt/bundled/base.h>

#include "tools/logger/logger_define.hpp"
export module gol;
import :map;
import bik.playground;
import bik.settings;
import bik.logger;
namespace gol {
    export class GameOfLife : public bik::playground::BasePlayGround {
    public:
        GameOfLife() {
            LOGGER->info("GameOfLife::GameOfLife()");
        }

        void update() override{}

        void initialize() override {
            LOGGER->info("GameOfLife::initialize()");
            if (settings_.get_or_set("/Gol/Rules/Autostart"_json_pointer, true)) {
                new_gol();
            }
        }

        void new_gol() {
            LOGGER->info("GameOfLife::new_gol()");
            map_ = std::make_shared<Map>();
            map_->size = settings_.get_or_set("/Gol/Rules/Size"_json_pointer, sf::Vector2u(100, 100));
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
        std::shared_ptr<Map> map_ = nullptr;
    };
}
