/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine.cpp
 */
#include <ctime> // srand(time)
#include "engine.hpp"

#include "bintjekit/engine/play_ground.hpp"

float randf(float min, float max) {
    return min + (max - min) * (rand() / (RAND_MAX + 1.0f));
}

int randi(int min, int max) {
    return min + rand() % (max - min + 1);
}

namespace usr {
    Engine::Engine() {
        srand(time(nullptr));
        new_world();
    }

    Engine::~Engine() = default;


    void Engine::configure() {
    }

    void Engine::initialise() {
    }

    void Engine::on_sfml_event(const sf::Event &event) {
    }

    void Engine::update() {
        IEngine::update(); // Update m_play_ground
        m_circle_position += m_circle_speed;
        collision_detection();
    }

    void Engine::new_world() {
        m_circle_position = sf::Vector2f(
            randf(m_play_ground->position.x, m_play_ground->position.x + m_play_ground->size.x),
            randf(m_play_ground->position.y, m_play_ground->position.y + m_play_ground->size.y));
        m_circle_radius = 100;
        m_circle_outline_thickness = 1;
        m_circle_color = sf::Color::Red;
        m_circle_outline_color = sf::Color::Black;
        m_background_color = sf::Color::Green;
        new_speed();
    }

    sf::Vector2f Engine::world_size() const {
        return m_play_ground->size;
    }

    long int Engine::ticks() const {
        return m_play_ground->ticks();
    }

    sf::Vector2f Engine::circle_position() const {
        return m_circle_position;
    }

    float Engine::circle_radius() const {
        return m_circle_radius;
    }

    sf::Color Engine::circle_color() const {
        return m_circle_color;
    }

    sf::Color Engine::circle_outline_color() const {
        return m_circle_outline_color;
    }

    sf::Color Engine::background_color() const {
        return m_background_color;
    }

    sf::Vector2f Engine::circle_speed() const {
        return m_circle_speed;
    }

    float Engine::circle_outline_thickness() const {
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
        } else if (m_circle_position.x + m_circle_radius > m_play_ground->size.x) {
            m_circle_position.x = m_play_ground->size.x - m_circle_radius;
            collision = true;
        }
        if (m_circle_position.y - m_circle_radius < 0) {
            m_circle_position.y = m_circle_radius;
            collision = true;
        } else if (m_circle_position.y + m_circle_radius > m_play_ground->size.y) {
            m_circle_position.y = m_play_ground->size.y - m_circle_radius;
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
