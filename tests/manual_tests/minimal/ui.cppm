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
        explicit UI(bik::window::BaseWindow *window, bik::renderer::BaseRenderer *renderer,
                    bik::playground::BasePlayGround *base_playground) :
            BaseUI(window, renderer, base_playground),
            minplayground_(static_cast<min::PlayGround &>(*base_playground)) {
        }

        void update() override {
            event_handler();
            if (minplayground_.over()) {
                on_close();
            }
        }

        min::PlayGround &minplayground_;
    };
}
