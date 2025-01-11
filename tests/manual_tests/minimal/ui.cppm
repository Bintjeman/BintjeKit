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
export module min.ui;
export import bik.ui;
import min.playground;
namespace min {
export class UI :public bik::ui::BaseUI {
   public:
      void update() override {
        bik::ui::BaseUI::update();
            min::PlayGround& playground = dynamic_cast<min::PlayGround>(playground_);
          if (playground.over()) {

          }
      }
};
}
