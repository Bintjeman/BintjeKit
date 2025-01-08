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
import gol;
namespace gol {
    export class UserInterface : public bik::ui::BaseUI {
    public:
        explicit UserInterface(){}
        void set_playground(std::shared_ptr<bik::playground::BasePlayGround> game_of_life) override{
            LOGGER->info("UserInterface::set_playground()");
            BaseUI::set_playground(game_of_life);
            game_of_life_ = std::dynamic_pointer_cast<GameOfLife>(game_of_life);
        }

        void key_pressed(const ::sf::Event::KeyPressed &event) override {
            switch (event.scancode) {
                case sf::Keyboard::Scancode::Q:
                    if (event.control) {
                        on_close();
                    }
                    break;
                case sf::Keyboard::Scancode::N:
                    if (event.control) {
                        game_of_life_->new_gol();
                    }
                    break;
                case sf::Keyboard::Scancode::K:
                    if (event.control) {
                        game_of_life_->kill_gol();
                    }
                    break;
            }
        }

    private:
        std::shared_ptr<GameOfLife> game_of_life_;
    };
}
