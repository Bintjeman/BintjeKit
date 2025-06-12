/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_engine.hpp
 */
#ifndef I_ENGINE_HPP
#define I_ENGINE_HPP
#pragma once
#include "SFML/Window/Event.hpp"

namespace bnjkit {
    namespace engine {
        class IEngine {
        public:
            virtual ~IEngine();
            virtual void initialise() =0;
            virtual void configure() =0;
            virtual void on_sfml_event(const sf::Event &event) =0;
            virtual void update() = 0;
        protected:

        };
    } // engine
} // bnjkit

#endif //I_ENGINE_HPP
