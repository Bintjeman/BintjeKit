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
namespace bik::ui {
    export class BaseUI {
    public:
        explicit BaseUI(window::BaseWindow& window);
        virtual void configure();
        virtual void initialize();
        virtual void update();
        virtual void finalize();

    protected:
        void event_handler(sf::Event &event);
        bik::window::BaseWindow& window_;
    };


}
