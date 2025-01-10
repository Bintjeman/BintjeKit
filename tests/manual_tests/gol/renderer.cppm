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
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
export module gol.renderer;
import bik.renderer;
import bik.playground;
import gol;
import bik.common;
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
            target_->setView(playground_view_);
            target_->draw(shape);
            static sf::Text text(font_);
            auto playground_frequency = std::format("{:.2f}", core_info_provider_->playground_frequency());
            auto renderer_frequency = std::format("{:.2f}", core_info_provider_->renderer_frequency());
            text.setString("SPS:" + playground_frequency + "\nFPS:" + renderer_frequency);
            target_->setView(ui_view_);
            target_->draw(text);
        }
    private:
        std::shared_ptr<GameOfLife> game_of_life_;
    };
}
