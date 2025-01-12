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
namespace bik {
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
    namespace imguiwrapper {
        export class BaseImGuiWrapper;
    }
}
namespace bik::factory {

    export class BaseFactory {
    public:
        BaseFactory();
        virtual ~BaseFactory();
        virtual void creation();
        virtual void clear();

        std::shared_ptr<window::BaseWindow> window() const;
        std::shared_ptr<ui::BaseUI> ui() const;
        std::shared_ptr<playground::BasePlayGround> playground() const;
        std::shared_ptr<renderer::BaseRenderer> renderer() const;
        std::shared_ptr<imguiwrapper::BaseImGuiWrapper> imgui_wrapper() const;

    protected:
        virtual void build_window();
        virtual void build_ui();
        virtual void build_playground();
        virtual void build_renderer();
        virtual void build_imgui_wrapper();
        std::shared_ptr<window::BaseWindow> window_ = nullptr;
        std::shared_ptr<ui::BaseUI> ui_ = nullptr;
        std::shared_ptr<playground::BasePlayGround> playground_ = nullptr;
        std::shared_ptr<renderer::BaseRenderer> renderer_ = nullptr;
        std::shared_ptr<imguiwrapper::BaseImGuiWrapper> imgui_wrapper_ = nullptr;

    private:
        virtual void pre_build_window();
        virtual void pre_build_ui();
        virtual void pre_build_playground();
        virtual void pre_build_renderer();
        virtual void pre_build_imgui_wrapper();
    };
}
