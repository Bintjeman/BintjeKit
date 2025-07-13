/*!
 * @author bintjeman
 * @date 01.07.25
 * @name evobotrenderer.cpp
 */

#include "evobot_renderer.hpp"

#include <bintjekit/engine/i_engine.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <bintjekit/configuration/sfml_json_adapter.hpp>
#include <bintjekit/engine/play_ground.hpp>

#include "evobot_engine/evobot_engine.hpp"
#include "evobot_engine/evo_world.hpp"

namespace evo::renderer {
    EvobotRenderer::EvobotRenderer() = default;
    void EvobotRenderer::get_drawable(
        std::vector<std::reference_wrapper<sf::Drawable> >& drawable_list
    ) const {
        static sf::RectangleShape bg;

        // Background rendering reste le même
        if (m_draw_background) {
            auto world = m_evobot_engine->world();
            sf::FloatRect rect = world->play_ground().bounds();
            bg.setSize(rect.size);
            bg.setPosition(rect.position);
            bg.setFillColor(m_back_ground_color);
            drawable_list.emplace_back(bg);
        }


        // Rendu des Evobots


        // Rendu des Globs

    }

    std::string EvobotRenderer::name() const {
        return "EvobotRenderer";
    }

    void EvobotRenderer::configure() {
        m_logger->info("EvobotRenderer: configuring");
        m_draw_background = m_custom_settings.get_or_set("/Draw background", true);
        m_draw_evobots = m_custom_settings.get_or_set("/Draw evobots", true);
        m_draw_globs = m_custom_settings.get_or_set("/Draw globs", true);
        m_back_ground_color = m_custom_settings.get_or_set(
            "/Renderer/Color/Background",
            sf::Color{100, 100, 100}
        );
        m_evobot_color = m_custom_settings.get_or_set("/Color/Evobot",
                                                      sf::Color{255, 0, 0}
        );
        m_evobot_color_2 = m_custom_settings.get_or_set("/Color/Evobot2",
                                                        sf::Color{200, 50, 0}
        );
        m_glob_color = m_custom_settings.get_or_set("/Color/Glob",
                                                    sf::Color{0, 255, 0}
        );
        m_glob_color_2 = m_custom_settings.get_or_set("/Color/Glob2",
                                                      sf::Color{0, 200, 50}
        );
    }

    sf::Rect<float> EvobotRenderer::get_bounds() const {
        const auto *world = m_evobot_engine->world();
        if (world) {
            return sf::Rect<float>{world->play_ground().bounds()};
        }else {
            return sf::Rect<float>{};
        }
    }

    void EvobotRenderer::set_engine(const bnjkit::engine::IEngine* engine) {
        IEngineRenderer::set_engine(engine);
        m_evobot_engine = dynamic_cast<const engine::EvobotEngine*>(engine);
    }
}
