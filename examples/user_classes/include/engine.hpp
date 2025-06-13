/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine.hpp
 */
#ifndef ENGINE_HPP
#define ENGINE_HPP
#pragma once
#include <SFML/Graphics/Color.hpp>
#include "bintjekit/engine/i_engine.hpp"
#include "SFML/Graphics/CircleShape.hpp"

namespace usr {
    class Engine : public bnjkit::engine::IEngine {
    public:
        Engine();
        ~Engine() override;
        void initialise() override;
        void configure() override;
        void on_sfml_event(const sf::Event &event) override;
        void update() override;
        void new_world();
        [[nodiscard]] long int get_tick_counter() const;
        [[nodiscard]] sf::Vector2f get_window_size() const;
        [[nodiscard]] sf::Vector2f get_circle_position() const;
        [[nodiscard]] float get_circle_radius() const;
        [[nodiscard]] sf::Color get_circle_color() const;
        [[nodiscard]] sf::Color get_circle_outline_color() const;
        [[nodiscard]] sf::Color get_background_color() const;
        [[nodiscard]] sf::Vector2f get_circle_speed() const;
        [[nodiscard]] float get_circle_outline_thickness() const;

    private:
        void new_speed();
        void collision_detection();
        sf::Vector2f m_window_size;
        sf::Vector2f m_circle_speed;
        sf::Vector2f m_circle_position;
        float m_circle_radius;
        float m_circle_outline_thickness;
        sf::Color m_circle_color;
        sf::Color m_circle_outline_color;
        sf::Color m_background_color;
        long int m_tick_counter;
    };
} // usr
#endif //ENGINE_HPP
