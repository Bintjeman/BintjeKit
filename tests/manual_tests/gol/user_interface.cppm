/*!
 * @file user_interface.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <set>
#include <SFML/Window/Event.hpp>
#include "tools/logger/logger_define.hpp"
export module gol.user_interface;
import bik.ui;
import bik.window;
import bik.playground;
import bik.renderer;
import gol;
namespace gol {
    export class UserInterface : public bik::ui::BaseUI {
    public:
        explicit UserInterface() {
        }

        void set_playground(std::shared_ptr<bik::playground::BasePlayGround> game_of_life) override {
            LOGGER->info("UserInterface::set_playground()");
            BaseUI::set_playground(game_of_life);
            game_of_life_ = std::dynamic_pointer_cast<GameOfLife>(game_of_life);
        }

        void key_pressed(const ::sf::Event::KeyPressed &key_event) override {
            switch (key_event.scancode) {
                case sf::Keyboard::Scancode::Q:
                    if (key_event.control) {
                        on_close();
                    }
                    break;
                case sf::Keyboard::Scancode::N:
                    if (key_event.control) {
                        game_of_life_->new_gol();
                    }
                    break;
                case sf::Keyboard::Scancode::K:
                    if (key_event.control) {
                        game_of_life_->kill_gol();
                    }
                    break;
                case sf::Keyboard::Scancode::A:
                    renderer_->camera_move(sf::Vector2f(-1, 0));
                    break;
                case sf::Keyboard::Scancode::D:
                    renderer_->camera_move(sf::Vector2f(1, 0));
                    break;
                case sf::Keyboard::Scancode::W:
                    renderer_->camera_move(sf::Vector2f(0, -1));
                    break;
                case sf::Keyboard::Scancode::S:
                    renderer_->camera_move(sf::Vector2f(0, 1));
                    break;
                case sf::Keyboard::Scancode::C:
                    if (key_event.control) {
                        renderer_->reframe();
                    }
            }
        }

        void mouse_scrolled(const sf::Event::MouseWheelScrolled &scrolled_event) override {
            LOGGER->trace("Mouse scrolled");
            float scrolled = scrolled_event.delta;
            if (scrolled > 0) {
                renderer_->camera_zoom(1.1f);
            } else if (scrolled < 0) {
                renderer_->camera_zoom(0.9f);
            }
        }

    private:
        std::shared_ptr<GameOfLife> game_of_life_;
    };
}
