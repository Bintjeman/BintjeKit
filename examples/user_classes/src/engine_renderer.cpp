/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine_renderer.cpp
 */

#include "engine_renderer.hpp"

#include <memory>

#include "SFML/Graphics/CircleShape.hpp"
#include "engine.hpp"
#include "bintjekit/engine/play_ground.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

namespace usr {
    EngineRenderer::~EngineRenderer() = default;

    void EngineRenderer::get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const {
        static sf::RectangleShape background(m_engine->play_ground().size);
        static sf::CircleShape circle(100.f);
        // Text
        background.setFillColor(m_usr_engine->background_color());
        drawable_list.emplace_back(std::ref(background));
        // Circle
        circle.setRadius(m_usr_engine->circle_radius());
        circle.setFillColor(m_usr_engine->circle_color());
        circle.setOutlineColor(m_usr_engine->circle_outline_color());
        circle.setOutlineThickness(m_usr_engine->circle_outline_thickness());
        circle.setPosition(m_usr_engine->circle_position());
        drawable_list.emplace_back(std::ref(circle));
    }

    void EngineRenderer::set_engine(const bnjkit::engine::IEngine *engine) {
        IEngineRenderer::set_engine(engine);
        m_usr_engine = dynamic_cast<const Engine *>(engine);
    }

    sf::Rect<float> EngineRenderer::get_bounds() const {
        return {m_engine->play_ground().bounds()};
    }
    std::string EngineRenderer::name() const {
        return "EngineRenderer";
    }
} // usr
