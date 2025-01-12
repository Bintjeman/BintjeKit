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
export import bik.settings;
// namespace sf {
    // class RenderTarget;
// }
namespace bik {
    namespace playground {
        export class BasePlayGround;
    }

    namespace common {
        class BaseCoreInfoProvider;
    }
}

namespace bik::renderer {
    export class BaseRenderer {
    public:
        BaseRenderer();
        virtual ~BaseRenderer();
        virtual void configure(config::Child settings);
        virtual void initialize();
        virtual void update();
        virtual void finalize();
        virtual void draw();
        virtual void set_target(std::shared_ptr<sf::RenderTarget> target);
        virtual void set_playground(std::shared_ptr<playground::BasePlayGround> playground);
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
        std::shared_ptr<sf::RenderTarget> target_ = nullptr;
        std::shared_ptr<playground::BasePlayGround> playground_ = nullptr;
        common::BaseCoreInfoProvider *core_info_provider_ = nullptr;
    };
}
