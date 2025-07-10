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

#include "arrow_render_system.hpp"
#include "evobot_engine/entity.hpp"
#include "evobot_engine/evobot.hpp"
#include "evobot_engine/evobot_engine.hpp"
#include "evobot_engine/glob.hpp"

namespace evo {
    namespace renderer {
        void EvobotRenderer::get_drawable(
            std::vector<std::reference_wrapper<sf::Drawable> >& drawable_list
        ) const {
            static sf::RectangleShape bg;
            static sf::CircleShape circle;
            static std::vector<sf::CircleShape> circles;
            circles.clear();
            if (m_draw_background) {
                sf::FloatRect rect = m_engine->play_ground().bounds();
                bg.setSize(rect.size);
                bg.setPosition(rect.position);
                bg.setFillColor(m_back_ground_color);
                drawable_list.emplace_back(bg);
            }
            ArrowRenderSystem::append_drawables(drawable_list, m_evobot_engine->entity_manager());
            circles.reserve(m_evobot_engine->entity_manager().size());
            if (m_draw_evobots) {
                circle.setFillColor(m_evobot_color);
                circle.setFillColor(m_evobot_color_2);
                circle.setOutlineThickness(1.f);
                for (const auto& evobot: m_evobot_engine->entity_manager().get_collection<engine::Evobot>().
                     typed_entities()) {
                    if (evobot) {
                        circle.setPosition(evobot->bounds().position);
                        circle.setRadius(evobot->radius());
                        circles.emplace_back(circle);
                        drawable_list.emplace_back(circles.back());
                    }
                }
            }
            if (m_draw_globs) {
                circle.setFillColor(m_glob_color);
                circle.setFillColor(m_glob_color_2);
                circle.setOutlineThickness(1.f);
                for (const auto& glob: m_evobot_engine->entity_manager().get_collection<engine::Glob>().
                     typed_entities()) {
                    if (glob) {
                        circle.setPosition(glob->bounds().position);
                        circle.setRadius(glob->radius());
                        circles.emplace_back(circle);
                        drawable_list.emplace_back(circles.back());
                    }
                }
            }
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
            return m_engine->play_ground().bounds();
        }

        void EvobotRenderer::set_engine(const bnjkit::engine::IEngine* engine) {
            IEngineRenderer::set_engine(engine);
            m_evobot_engine = dynamic_cast<const engine::EvobotEngine*>(engine);
        }
    } // renderer
} // evo
