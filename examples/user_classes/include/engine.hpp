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
        void on_sfml_event(const sf::Event& event) override;
        void update() override;
        void new_world();
        // Playground
        [[nodiscard]] sf::Vector2f world_size() const;
        [[nodiscard]] long int ticks() const;
        // Circle
        [[nodiscard]] sf::Vector2f circle_position() const;
        [[nodiscard]] float circle_radius() const;
        [[nodiscard]] sf::Color circle_color() const;
        [[nodiscard]] sf::Color circle_outline_color() const;
        [[nodiscard]] sf::Color background_color() const;
        [[nodiscard]] sf::Vector2f circle_speed() const;
        [[nodiscard]] float circle_outline_thickness() const;

    private:
        void new_speed();
        void collision_detection();
        static int randi(int min, int max);
        static float randf();
        static float randf(float min, float max);
        sf::Vector2f m_circle_speed;
        sf::Vector2f m_circle_position;
        float m_circle_radius{};
        float m_circle_outline_thickness{};
        sf::Color m_circle_color;
        sf::Color m_circle_outline_color;
        sf::Color m_background_color;
    };
} // usr
#endif //ENGINE_HPP
