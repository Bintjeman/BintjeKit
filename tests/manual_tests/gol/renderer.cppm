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
        void set_playground(const std::shared_ptr<bik::playground::BasePlayGround>& playground) override {
            BaseRenderer::set_playground(playground);
            game_of_life_ = std::dynamic_pointer_cast<GameOfLife>(playground);
        }

        void draw() override {
            target_->setView(playground_view_);
            game_of_life_->prerendering();
            target_->draw(game_of_life_->drawable());
            // UI
            static sf::Text text(font_);
            auto playground_frequency = std::format("{:.2f}", core_info_provider_->playground_effective_frequency());
            auto renderer_frequency = std::format("{:.2f}", core_info_provider_->renderer_effective_frequency());
            text.setString("SPS:" + playground_frequency + "\nFPS:" + renderer_frequency);
            target_->setView(ui_view_);
            target_->draw(text);
        }

    private:
        std::shared_ptr<GameOfLife> game_of_life_;
        sf::Font font_;
    };
}
