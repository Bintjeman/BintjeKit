/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine.cpp
 */
#include <ctime> // srand(time)
#include "engine.hpp"

#include "bintjekit/engine/play_ground.hpp"

namespace usr {
    Engine::Engine() {
        srand(static_cast<unsigned int>(time(nullptr)));
        new_world();
    }

    Engine::~Engine() = default;

    void Engine::configure() {
    }

    void Engine::initialise() {
    }

    void Engine::on_sfml_event(const sf::Event& event[[maybe_unused]]) {
    }

    void Engine::update() {
        IEngine::update(); // Update m_play_ground
        m_circle_position += m_circle_speed;
        collision_detection();
    }

    void Engine::new_world() {
        m_play_ground->size = {1'000, 1'000};
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
            (randf() * 2.f - 1.f) * speed,
            (randf() * 2.f - 1.f) * speed
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
                static_cast<unsigned char>(rand() % 256), // R
                static_cast<unsigned char>(rand() % 256), // G
                static_cast<unsigned char>(rand() % 256) // B
            );
            new_speed();
        }
    }
    int Engine::randi(int min, int max) {
        return rand() * (max + min) - min;
    }
    float Engine::randf() {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    float Engine::randf(float min, float max) {
        return randf() * (max + min) - min;
    }
} // usr
