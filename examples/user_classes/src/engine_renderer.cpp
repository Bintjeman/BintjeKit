/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine_renderer.cpp
 */

#include "engine_renderer.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "engine.hpp""

namespace usr {
    EngineRenderer::~EngineRenderer() = default;

    void EngineRenderer::get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const {
        static sf::CircleShape circle(100.f);
        circle.setFillColor(sf::Color::Red);
        drawable_list.emplace_back(std::ref(circle));
    }
} // usr
