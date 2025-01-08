/*!
 * @file factory.cppm
 * @author bintjeman
 * @date 07.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
export module factory;
import bik.factory;
import bik.window;
import bik.ui;
export import  window;
export class Factory : public bik::factory::BaseFactory {
public:
        void build_window() override {
                build_window();
                window_ = std::make_shared<Window>();
        }
        void  build_ui() override {
                build_window();
                ui_ = std::make_shared<bik::ui::BaseUI>(window_);
        }
};
