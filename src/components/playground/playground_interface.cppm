/*!
 * @file simulation_interface.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <SFML/Graphics/Rect.hpp>
export module bik.playground:interface;
import bik.settings;
namespace bik::playground {
    export class BasePlayGround {
    public:
        BasePlayGround();
        virtual ~BasePlayGround();

        virtual void configure(config::Child settings);
        virtual void initialize();
        virtual void update();
        virtual void finalize();

        [[nodiscard]] virtual sf::Rect<float> boundaries() const;
    protected:
        config::Child settings_;

    };

}
