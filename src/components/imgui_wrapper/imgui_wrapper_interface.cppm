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
}

namespace bik::imguiwrapper {
    export class BaseImGuiWrapper {
    public:
        BaseImGuiWrapper();
        ~BaseImGuiWrapper();
        void set_window(const std::shared_ptr<window::BaseWindow> &window);
        void initialize();
        void finalize();
        void update();
        virtual void render();

    private:
        std::shared_ptr<window::BaseWindow> window_;
        sf::Clock clock;
    };
}
