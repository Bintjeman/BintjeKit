/*!
 * @file imgui_wrapper_interface.cppm
 * @author bintjeman
 * @date 12.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <SFML/System/Clock.hpp>
export module bik.imgui_wrapper:interface;
namespace bik {
    namespace window {
        export class BaseWindow;
    }

    namespace playground {
        export class BasePlayGround;
    }

    namespace common {
        export class BaseCoreInfoProvider;
    }
}

namespace bik::imguiwrapper {
    export class BaseImGuiWrapper {
    public:
        BaseImGuiWrapper();
        virtual ~BaseImGuiWrapper();
        void set_window(const std::shared_ptr<window::BaseWindow> &window);
        void set_core_info_provider(common::BaseCoreInfoProvider *core_info_provider);
        void set_playground(const std::shared_ptr<playground::BasePlayGround> &playground);
        void initialize();
        void finalize();
        void update();
        virtual void draw();
        void render();

    protected:
        common::BaseCoreInfoProvider *core_info_provider_ = nullptr;

    private:
        sf::Clock clock;
        std::shared_ptr<window::BaseWindow> window_;
        std::shared_ptr<playground::BasePlayGround> playground_;
    };
}
