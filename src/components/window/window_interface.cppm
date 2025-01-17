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
export import bik.settings;
namespace bik::window {
    export class BaseWindow : public sf::RenderWindow, public settings::HasSettings {
    public:
        explicit BaseWindow();
        ~BaseWindow() override;

        void initialize() override;
        virtual void open();
        virtual void finalize();

    protected:
        std::string start_title_{};
        sf::Vector2u start_size_{200, 200};
        sf::Vector2i start_pos_{100, 100};

    private:
    };
}
