/*!
 * @author bintjeman
 * @date 14.06.25
 * @name renderer.cpp
 */
#include "renderer.hpp"
namespace gol {
    void Renderer::on_sfml_event(const sf::Event &event) {
        if (const auto &resized = event.getIf<sf::Event::Resized>()) {
            resize_views();
        }
    }
} // gol
