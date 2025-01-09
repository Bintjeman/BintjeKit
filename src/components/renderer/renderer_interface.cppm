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
export module bik.renderer:interface;
namespace sf {
    class RenderTarget;
}
namespace bik {
    namespace playground {
        class BasePlayGround;
    }
}

namespace bik::renderer {
    export class BaseRenderer {
    public:
        BaseRenderer();
        virtual ~BaseRenderer();
        virtual void draw();
        virtual void set_target(std::shared_ptr<sf::RenderTarget> target);
        virtual void set_playground(std::shared_ptr<playground::BasePlayGround> playground);

        void set_view(sf::View view);
        void camera_move(sf::Vector2f offset);
        void camera_zoom(float zoom);
        void reframe();
    protected:
        std::shared_ptr<sf::RenderTarget> target_ = nullptr;
        std::shared_ptr<playground::BasePlayGround> playground_ = nullptr;
        sf::View main_view_;
        sf::View playground_view_;
        sf::View ui_view_;

    };
}
