/*!
 * @file ui_interface.cppm
 * @author bintjeman
 * @date 07.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <SFML/Window/Event.hpp>
export module bik.ui:interface;
namespace bik {
    namespace window {
        export class BaseWindow;
    }
    namespace imguiwrapper {
        export class BaseImGuiWrapper;
    }
    namespace renderer {
        export class BaseRenderer;
    }
    namespace playground {
        export class BasePlayGround;
    }
    namespace common {
        export class BaseIActionReceiver;
    }

}
namespace bik {
    namespace ui {
        export class BaseUI {
        public:
            explicit BaseUI();
            virtual ~BaseUI();

            virtual void configure();
            virtual void initialize();
            virtual void update();
            virtual void finalize();

            void set_action_receiver(common::BaseIActionReceiver *action_receiver);
            virtual void set_playground(std::shared_ptr<playground::BasePlayGround> playground);
            virtual void set_renderer(std::shared_ptr<renderer::BaseRenderer> renderer);
            virtual void set_window(std::shared_ptr<window::BaseWindow> window);
            virtual void set_imgui_wrapper(std::shared_ptr<imguiwrapper::BaseImGuiWrapper> imgui_wrapper);

        protected:
            virtual void event_handler();
            virtual void key_pressed(const sf::Event::KeyPressed &key_event);
            virtual void resized(const sf::Event::Resized &size_event);
            virtual void mouse_scrolled(const sf::Event::MouseWheelScrolled &scroll_event);
            void on_close();

            std::shared_ptr<window::BaseWindow> window_;
            std::shared_ptr<playground::BasePlayGround> playground_ = nullptr;
            std::shared_ptr<renderer::BaseRenderer> renderer_ = nullptr;
            std::shared_ptr<imguiwrapper::BaseImGuiWrapper> imgui_wrapper_ = nullptr;
            common::BaseIActionReceiver *action_receiver_ = nullptr;

        private:

        };
    }
}
