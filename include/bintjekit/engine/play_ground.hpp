/*!
 * @author bintjeman
 * @date 14.06.25
 * @name play_ground.hpp
 */

#ifndef BNJKIT_ENGINE_PLAY_GROUND_HPP
#define BNJKIT_ENGINE_PLAY_GROUND_HPP
#pragma once

#include <memory>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include <spdlog/fwd.h>

namespace bnjkit {
    namespace engine {
        struct PlayGround {
        public:
            PlayGround();
            ~PlayGround();
            void initialise();
            void configure();
            void update();
            [[nodiscard]] long int ticks() const;
            [[nodiscard]] sf::Rect<float> bounds() const;
            sf::Vector2f size = {0.f, 0.f};
            sf::Vector2f position = {0.f, 0.f};

        protected:
            std::shared_ptr<spdlog::logger> m_logger;

        private:
            long int ticks_counter = 0;
        };
    } // engine
} // bnjkit

#endif // BNJKIT_ENGINE_PLAY_GROUND_HPP
