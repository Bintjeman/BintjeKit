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
export module window:interface;
import settings_manager;
namespace bik::window {
    export class Window : public sf::RenderWindow {
    public:
        Window();
        ~Window() override;

        virtual void configure(const config::Node& settings);
        virtual void initialize();
        virtual void open();
        virtual void finalize();

    protected:
        std::string start_title_{};
        sf::Vector2u start_size_{200, 200};
        sf::Vector2i start_pos_{100, 100};

        config::Node settings_;
    public:
        // Debug et test
        [[deprecated("Seulement pour des tests")]]
        virtual void hw();

    private:

    };
}
