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
import bik.window;
import bik.common;
namespace bik {
    namespace ui {
        export class BaseUI {
        public:
            explicit BaseUI(window::BaseWindow &window);
            virtual void configure();
            virtual void initialize();
            virtual void update();
            virtual void finalize();

            void set_action_receiver(common::BaseIActionReceiver *action_receiver);

        protected:
            void event_handler();

            window::BaseWindow &window_;
            common::BaseIActionReceiver* action_receiver_;
        private:
            void on_close();
            void key_pressed(const sf::Event::KeyPressed &event);
            void resized(const sf::Event::Resized &event);
            void mouse_scrolled(const sf::Event::MouseWheelScrolled &event);
        };
    }
}
