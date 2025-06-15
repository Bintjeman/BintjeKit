/*!
 * @author bintjeman
 * @date 15.06.25
 * @name default_renderer.hpp
 */

#ifndef DEFAULT_RENDERER_HPP
#define DEFAULT_RENDERER_HPP
#pragma once
#include "i_renderer.hpp"
namespace bnjkit {
    namespace renderer {
        class DefaultRenderer : public IRenderer {
        public:
            void on_sfml_event(const sf::Event &event) override;
            void render_scene() override ;
        };
    } // renderer
} // bnjkit
#endif //DEFAULT_RENDERER_HPP
