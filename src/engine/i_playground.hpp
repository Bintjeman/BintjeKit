/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_playground.hpp
 */

#ifndef I_PLAYGROUND_HPP
#define I_PLAYGROUND_HPP
#pragma once
#include <SFML/Graphics/Drawable.hpp>

namespace bnjkit {
    namespace engine {
        class IPlayground : public sf::Drawable {
            virtual ~IPlayground();
            virtual void initialise() =0;
            virtual void configure() =0;
            virtual void on_sfml_event(const sf::Event &event) =0;
            virtual void update() = 0;

        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        };
    } // engine
} // bnjkit

#endif //I_PLAYGROUND_HPP
