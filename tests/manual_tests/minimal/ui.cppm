/*!
 * @file ui.cppm
 * @author bintjeman
 * @date 11.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
export module min.ui;
export import bik.ui;
import min.playground;
namespace min {
    export class UI : public bik::ui::BaseUI {
    public:
        void update() override {
            event_handler();
            min::PlayGround &playground = *std::dynamic_pointer_cast<min::PlayGround>(playground_);
            if (playground.over()) {
                on_close();
            }
        }
    };
}
