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
#include <map>
export module bik.factory:interface;
namespace bik {
    namespace component {
        export class BaseComponent;
    }
    namespace ui {
        export class BaseUI;
    }
    namespace window {
        export class BaseWindow;
    }
    namespace playground {
        export class BasePlayGround;
    }
    namespace renderer {
        export class BaseRenderer;
    }
}
namespace bik::factory {

    export class BaseFactory {
    public:
        BaseFactory();
        virtual ~BaseFactory();
        virtual void creation();
        virtual void clear();

        std::unique_ptr<window::BaseWindow> consume_window() ;
        std::unique_ptr<ui::BaseUI> consume_ui() ;
        std::unique_ptr<playground::BasePlayGround> consume_playground() ;
        std::unique_ptr<renderer::BaseRenderer> consume_renderer() ;

    protected:
        virtual void build_window();
        virtual void build_ui();
        virtual void build_playground();
        virtual void build_renderer();

        window::BaseWindow* window_ptr_from_unique();
        ui::BaseUI* ui_ptr_from_unique();
        playground::BasePlayGround* playground_ptr_from_unique();
        renderer::BaseRenderer* renderer_ptr_from_unique();

        window::BaseWindow& window_ref_from_unique();
        ui::BaseUI& ui_ref_from_unique();
        playground::BasePlayGround& playground_ref_from_unique();
        renderer::BaseRenderer& renderer_ref_from_unique();

        std::map<std::string, std::unique_ptr<component::BaseComponent>> components_;
    private:
        virtual void pre_build_window();
        virtual void pre_build_ui();
        virtual void pre_build_playground();
        virtual void pre_build_renderer();
    };
}
