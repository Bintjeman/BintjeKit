/*!
 * @author bintjeman
 * @date 15.06.25
 * @name default_renderer.hpp
 */

#ifndef BNJKIT_RENDERER_DEFAULT_RENDERER_HPP
#define BNJKIT_RENDERER_DEFAULT_RENDERER_HPP
#pragma once
#include "i_renderer.hpp"
namespace bnjkit {
    namespace renderer {
        class DefaultRenderer : public IRenderer {
        public:
            void on_sfml_event(const sf::Event &event) override;
            void render_scene() override ;
            [[nodiscard]] std::string name() const override;
        };
    } // renderer
} // bnjkit
#endif // BNJKIT_RENDERER_DEFAULT_RENDERER_HPP
