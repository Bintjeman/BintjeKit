/*!
 * @file factory_interface.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
export module bik.factory:interface;
import bik.ui;
import bik.window;
namespace bik::factory {
    export class BaseFactory {
    public:
        BaseFactory();
        virtual ~BaseFactory();
        virtual void creation();
        virtual void clear();

        std::shared_ptr<window::BaseWindow> window() const;
        std::shared_ptr<ui::BaseUI> ui() const;

    protected:
        virtual void build_window();
        virtual void build_ui();
        std::shared_ptr<window::BaseWindow> window_ = nullptr;
        std::shared_ptr<ui::BaseUI> ui_ = nullptr;
    private:
        virtual void pre_build_window();
        virtual void pre_build_ui();
    };
}
