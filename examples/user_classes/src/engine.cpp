/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine.cpp
 */

#include "engine.hpp"

namespace usr {
    Engine::Engine() {
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
    }

    void Engine::new_world() {
        m_tick_counter = 0;
        m_circle_position = sf::Vector2f(0, 0);
        m_circle_radius = 10;
        m_circle_outline_thickness = 1;
        m_circle_color = sf::Color::Red;
        m_circle_outline_color = sf::Color::Black;
        new_speed();
    }

    long int Engine::get_tick_counter() const {
        return m_tick_counter;
    }

    void Engine::new_speed() {
        m_circle_speed = sf::Vector2f(static_cast<float>(rand() / RAND_MAX) - 0.5f,
                                      static_cast<float>(rand() / RAND_MAX) - 0.5f);
    }

    void Engine::collision_detection() {
        if (m_circle_position.x < 0 || m_circle_position.x > m_window_size.x) {
            on_collision();
        }
        if (m_circle_position.y < 0 || m_circle_position.y > m_window_size.y) {
            on_collision();
        }
    }

    void Engine::on_collision() {
        new_speed();
    }
} // usr
