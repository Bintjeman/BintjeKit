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
        void set_playground(std::shared_ptr<bik::playground::BasePlayGround> playground) override {
            minplayground_ = std::dynamic_pointer_cast<min::PlayGround>(playground);
        }
        void update() override {
            event_handler();
            if (minplayground_->over()) {
                on_close();
            }
        }
        std::shared_ptr<min::PlayGround> minplayground_;
    };
}
