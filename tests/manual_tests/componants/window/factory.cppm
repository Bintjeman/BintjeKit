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
                window_ = std::make_shared<Window>(*ui_);
        }
        void  build_ui() override {
                ui_ = std::make_shared<bik::ui::BaseUI>();
        }
};
