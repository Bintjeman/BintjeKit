/*!
 * @file window.cppm
 * @author bintjeman
 * @date 07.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
export module window;
import bik.window;
import bik.ui;
export class Window : public bik::window::BaseWindow{
    public:
        explicit Window(bik::ui::BaseUI& ui) : bik::window::BaseWindow(ui) {

        }
};
