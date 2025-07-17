/*!
 * @author bintjeman
 * @date 01.07.25
 * @name renderer.hpp
 */

#ifndef EVO_RENDERER_HPP
#define EVO_RENDERER_HPP
#pragma once
#include <bintjekit/renderer/i_renderer.hpp>

namespace evo {
    namespace engine {
        class EvobotEngine;
    }
    namespace renderer {
        class Renderer final : public bnjkit::renderer::IRenderer {
        public:
            void configure() override;
            [[nodiscard]] std::string name() const override;
            void camera_move(sf::Vector2f delta);
            void camera_zoom(float ratio);
            void set_engine(const bnjkit::engine::IEngine* world) override;

        private:
            const engine::EvobotEngine* m_evobot{nullptr};
        };
    } // renderer
} // evo

#endif // EVO_RENDERER_HPP
