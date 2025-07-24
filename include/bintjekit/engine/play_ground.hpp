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

namespace bnjkit::engine {
    struct PlayGround {
        PlayGround();
        explicit PlayGround(const sf::Rect<float>& bounds);
        PlayGround(const sf::Vector2f& position, const sf::Vector2f& size);
        ~PlayGround();
        void initialise() const;
        void configure() const;
        void update();
        void cleanup();
        [[nodiscard]] long int ticks() const;
        void set_bounds(const sf::Rect<float>& bounds);
        void set_bounds(const sf::Vector2f& position, const sf::Vector2f& size);
        void set_position(const sf::Vector2f& position);
        void set_size(const sf::Vector2f& size);
        [[nodiscard]] sf::Rect<float> bounds() const;
        [[nodiscard]] sf::Vector2f size() const;
        [[nodiscard]] sf::Vector2f position() const;
        // Data members

    private:
        long int m_ticks_counter = 0;
        sf::Rect<float> m_bounds{{0.f, 0.f}, {0.f, 0.f}};
        std::shared_ptr<spdlog::logger> m_logger;
    };
}

#endif // BNJKIT_ENGINE_PLAY_GROUND_HPP
