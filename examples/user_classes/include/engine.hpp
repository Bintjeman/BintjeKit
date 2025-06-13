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
        void get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const override;
        void new_world();
        long int get_tick_counter() const;
    private:
        void new_speed();
        void collision_detection();
        void on_collision();
        sf::Vector2f m_window_size;
        sf::Vector2f m_circle_speed;
        sf::Vector2f m_circle_position;
        float m_circle_radius;
        float m_circle_outline_thickness;
        sf::Color m_circle_color;
        sf::Color m_circle_outline_color;
        sf::Color m_background_color;
        long int m_tick_counter;
        mutable sf::CircleShape m_circle;
    };
} // usr
#endif //ENGINE_HPP
