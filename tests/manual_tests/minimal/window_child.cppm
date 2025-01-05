/*!
 * @file window_child.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
export module window_child;
import window;
namespace min {
    export class WindowChild : public bik::window::Window {
    public:
        ~WindowChild() override;
        void initialize() override;
        void hw() override;
    };


}
