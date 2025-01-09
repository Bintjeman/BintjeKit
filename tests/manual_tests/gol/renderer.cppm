/*!
 * @file renderer.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
export module gol.renderer;
import bik.renderer;
import bik.playground;
import gol;
namespace gol {
    export class Renderer : public bik::renderer::BaseRenderer {

        void set_playground(std::shared_ptr<bik::playground::BasePlayGround> playground) override {
            BaseRenderer::set_playground(playground);
            game_of_life_ = std::dynamic_pointer_cast<GameOfLife>(playground);
        }

        void draw() override {
            target_->clear(sf::Color::Black);
            sf::RectangleShape shape;
            sf::Vector2f sizef = sf::Vector2f(game_of_life_->get_size());
            shape.setSize(sizef);
            shape.setFillColor(sf::Color::Red);
            target_->draw(shape);
        }

    private:
        std::shared_ptr<GameOfLife> game_of_life_;
    };
}