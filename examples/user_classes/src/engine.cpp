/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine.cpp
 */
#include <ctime>

#include "engine.hpp"

namespace usr {
    Engine::Engine() {
        srand(time(nullptr));
        m_world_size = sf::Vector2f(1000, 1000); // Taille par défaut
        new_world();
    }

    Engine::~Engine() = default;

    void Engine::initialise() {
    }

    void Engine::configure() {
    }

    void Engine::on_sfml_event(const sf::Event &event) {
    }

    void Engine::update() {
        m_tick_counter++;
        m_circle_position += m_circle_speed;
        collision_detection();
    }

    void Engine::new_world() {
        m_tick_counter = 0;
        m_circle_position = sf::Vector2f(100, 100);
        m_circle_radius = 100;
        m_circle_outline_thickness = 1;
        m_circle_color = sf::Color::Red;
        m_circle_outline_color = sf::Color::Black;
        m_background_color = sf::Color::Green;
        new_speed();
    }

    long int Engine::get_tick_counter() const {
        return m_tick_counter;
    }

    sf::Vector2f Engine::get_world_size() const {
        return m_world_size;
    }

    sf::Vector2f Engine::get_circle_position() const {
        return m_circle_position;
    }

    float Engine::get_circle_radius() const {
        return m_circle_radius;
    }

    sf::Color Engine::get_circle_color() const {
        return m_circle_color;
    }

    sf::Color Engine::get_circle_outline_color() const {
        return m_circle_outline_color;
    }

    sf::Color Engine::get_background_color() const {
        return m_background_color;
    }

    sf::Vector2f Engine::get_circle_speed() const {
        return m_circle_speed;
    }

    float Engine::get_circle_outline_thickness() const {
        return m_circle_outline_thickness;
    }

    void Engine::new_speed() {
        float speed = .1f;
        m_circle_speed = sf::Vector2f(
            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 - 1.f) * speed,
            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 - 1.f) * speed
        );
    }

    void Engine::collision_detection() {
        bool collision = false;
        if (m_circle_position.x - m_circle_radius < 0) {
            m_circle_position.x = m_circle_radius;
            collision = true;
        } else if (m_circle_position.x + m_circle_radius > m_world_size.x) {
            m_circle_position.x = m_world_size.x - m_circle_radius;
            collision = true;
        }
        if (m_circle_position.y - m_circle_radius < 0) {
            m_circle_position.y = m_circle_radius;
            collision = true;
        } else if (m_circle_position.y + m_circle_radius > m_world_size.y) {
            m_circle_position.y = m_world_size.y - m_circle_radius;
            collision = true;
        }
        if (collision) {
            m_circle_color = sf::Color(
                rand() % 256, // R
                rand() % 256, // G
                rand() % 256 // B
            );
            new_speed();
        }
    }
} // usr
