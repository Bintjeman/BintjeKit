/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine.cpp
 */

#include "engine.hpp"

#include "SFML/Graphics/CircleShape.hpp"

namespace usr {
    Engine::Engine() {
        m_window_size = sf::Vector2f(800, 600); // Taille par défaut
        new_world();
    }

    Engine::~Engine() {
    }

    void Engine::initialise() {
    }

    void Engine::configure() {
    }

    void Engine::on_sfml_event(const sf::Event &event) {
        if (const auto *resized = event.getIf<sf::Event::Resized>()) {
            m_window_size = sf::Vector2f(resized->size.x, resized->size.y);
        }
    }

    void Engine::update() {
        m_tick_counter++;
        m_circle_position += m_circle_speed;
        collision_detection();
    }

    void Engine::get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const {
        drawable_list.clear();
        m_circle.setRadius(m_circle_radius);
        m_circle.setPosition(m_circle_position);
        m_circle.setOutlineThickness(m_circle_outline_thickness);
        m_circle.setOutlineColor(m_circle_outline_color);
        m_circle.setFillColor(m_circle_color);
        drawable_list.emplace_back(std::ref(m_circle));
    }

    void Engine::new_world() {
        m_tick_counter = 0;
        m_circle_position = sf::Vector2f(100, 100);
        m_circle_radius = 100;
        m_circle_outline_thickness = 1;
        m_circle_color = sf::Color::Red;
        m_circle_outline_color = sf::Color::Green;
        new_speed();
    }

    long int Engine::get_tick_counter() const {
        return m_tick_counter;
    }

    void Engine::new_speed() {
        // Vitesse plus raisonnable
        float speed = 0.05f; // pixels par frame
        m_circle_speed = sf::Vector2f(
            (static_cast<float>(rand()) / RAND_MAX * 2.0f - .1f) * speed,
            (static_cast<float>(rand()) / RAND_MAX * 2.0f - .1f) * speed
        );
    }

    void Engine::collision_detection() {
        bool collision = false;
        if (m_circle_position.x - m_circle_radius < 0) {
            m_circle_position.x = m_circle_radius;
            m_circle_speed.x = -m_circle_speed.x;
            collision = true;
        } else if (m_circle_position.x + m_circle_radius > m_window_size.x) {
            m_circle_position.x = m_window_size.x - m_circle_radius;
            m_circle_speed.x = -m_circle_speed.x;
            collision = true;
        }
        if (m_circle_position.y - m_circle_radius < 0) {
            m_circle_position.y = m_circle_radius;
            m_circle_speed.y = -m_circle_speed.y;
            collision = true;
        } else if (m_circle_position.y + m_circle_radius > m_window_size.y) {
            m_circle_position.y = m_window_size.y - m_circle_radius;
            m_circle_speed.y = -m_circle_speed.y;
            collision = true;
        }
        if (collision) {
            // Optionnel : changez la couleur lors des collisions
            m_circle_color = sf::Color(
                rand() % 256, // R
                rand() % 256, // G
                rand() % 256 // B
            );
            new_speed();
        }
    }

    void Engine::on_collision() {
        new_speed();
    }
} // usr
