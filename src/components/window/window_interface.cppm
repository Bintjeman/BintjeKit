/*!
 * @file window_interface.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <SFML/Graphics/RenderWindow.hpp>
export module bik.window:interface;
import bik.settings;
namespace bik::window {
    export class BaseWindow : public sf::RenderWindow {
    public:
        BaseWindow();
        ~BaseWindow() override;

        virtual void configure(const config::Child& settings);
        virtual void initialize();
        virtual void open();
        virtual void finalize();

    protected:
        std::string start_title_{};
        sf::Vector2u start_size_{200, 200};
        sf::Vector2i start_pos_{100, 100};

        config::Child settings_;

    private:

    };
}
