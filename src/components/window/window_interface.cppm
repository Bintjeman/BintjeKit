/*!
 * @file window_interface.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
export module window:interface;
namespace bik::window {
    export class Window {
    public:
        Window();
        virtual ~Window();
        virtual void hw();
    private:
    };
}
