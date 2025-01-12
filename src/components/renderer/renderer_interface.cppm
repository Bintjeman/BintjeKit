/*!
 * @file renderer_interface.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
export module bik.renderer:interface;
import bik.common;
export import bik.settings;
namespace bik {
    namespace playground {
        class BasePlayGround;
    }
    namespace window {
        class BaseWindow;
    }
}
namespace bik::renderer {
    export class BaseRenderer: public component::BaseComponent {
    public:
        BaseRenderer(window::BaseWindow* window, playground::BasePlayGround* playground);
        virtual ~BaseRenderer();
        virtual void configure(config::Child settings);
        virtual void initialize();
        virtual void update();
        virtual void finalize();
        virtual void draw();
        virtual void set_view();
        void set_core_info_provider(common::BaseCoreInfoProvider *core_info_provider);

        void set_view(sf::View view);
        void camera_move(sf::Vector2f offset);
        void camera_zoom(float zoom);
        void reframe();

    protected:
        config::Child settings_;
        sf::View main_view_;
        sf::View playground_view_;
        sf::View ui_view_;
        sf::Font font_;
        sf::RenderTarget& target_;
        playground::BasePlayGround& playground_;
        common::BaseCoreInfoProvider *core_info_provider_ = nullptr;
    };
}
