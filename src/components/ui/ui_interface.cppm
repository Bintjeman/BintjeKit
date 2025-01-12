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
import bik.common;
namespace bik {
    namespace window {
        export class BaseWindow;
    }

    namespace renderer {
        export class BaseRenderer;
    }

    namespace playground {
        export class BasePlayGround;
    }
}

namespace bik {
    namespace ui {
        export class BaseUI : public component::BaseComponent {
        public:
            explicit BaseUI(window::BaseWindow *window, renderer::BaseRenderer *renderer,
                            playground::BasePlayGround *playground);
            virtual ~BaseUI();


            virtual void configure();

            virtual void initialize();

            virtual void update();

            virtual void finalize();

            void set_action_receiver(common::BaseIActionReceiver *action_receiver);

        protected:
            virtual void event_handler();
            virtual void key_pressed(const sf::Event::KeyPressed &key_event);
            virtual void resized(const sf::Event::Resized &size_event);
            virtual void mouse_scrolled(const sf::Event::MouseWheelScrolled &scroll_event);
            void on_close();

            window::BaseWindow &window_;
            playground::BasePlayGround &playground_;
            renderer::BaseRenderer &renderer_;
            common::BaseIActionReceiver *action_receiver_ = nullptr;

        private:
        };
    }
}
