/*!
 * @author bintjeman
 * @date 01.07.25
 * @name evobotrenderer.hpp
 */

#ifndef  EVO_EVOBOTRENDERER_HPP
#define  EVO_EVOBOTRENDERER_HPP
#pragma once
#include <bintjekit/renderer/i_engine_renderer.hpp>

namespace evo {
    namespace engine {
        class EvobotEngine;
    }

    namespace renderer {
        class EvobotRenderer final : public bnjkit::renderer::IEngineRenderer {
        public:
            EvobotRenderer();
            ~EvobotRenderer() override;
            void set_engine(const bnjkit::engine::IEngine* engine) override;
            void configure() override;
            [[nodiscard]] sf::Rect<float> bounds() const override;
            [[nodiscard]] std::string name() const override;

        private:
            const engine::EvobotEngine* m_evobot_engine;
        };
    } // renderer
} // evo
#endif // EVO_EVOBOTRENDERER_HPP
