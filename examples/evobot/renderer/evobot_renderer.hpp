/*!
 * @author bintjeman
 * @date 01.07.25
 * @name evobotrenderer.hpp
 */

#ifndef  EVO_EVOBOTRENDERER_HPP
#define  EVO_EVOBOTRENDERER_HPP
#pragma once
#include <SFML/Graphics/Color.hpp>
#include <bintjekit/renderer/i_engine_renderer.hpp>

namespace evo {
    namespace engine {
        class EvobotEngine;
    }

    namespace renderer {
        class EvobotRenderer final : public bnjkit::renderer::IEngineRenderer {
        public:
            void get_drawable(
                std::vector<std::reference_wrapper<sf::Drawable> >& drawable_list) const override;
            [[nodiscard]] std::string name() const override;
            void configure() override;
            [[nodiscard]] sf::Rect<float> get_bounds() const override;
            void set_engine(const bnjkit::engine::IEngine* engine) override;

        private:
            const engine::EvobotEngine* m_evobot_engine;
            sf::Color m_back_ground_color;
            sf::Color m_evobot_color;
            sf::Color m_evobot_color_2;
            sf::Color m_glob_color;
            sf::Color m_glob_color_2;
            bool m_draw_background{true};
            bool m_draw_evobots{true};
            bool m_draw_globs{true};
        };
    } // renderer
} // evo
#endif // EVO_EVOBOTRENDERER_HPP
