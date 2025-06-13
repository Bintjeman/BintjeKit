/*!
 * @author bintjeman
 * @date 13.06.25
 * @name engine_renderer.hpp
 */

#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP
#pragma once
#include "bintjekit/renderer/i_engine_renderer.hpp"

namespace usr {
    class EngineRenderer : public bnjkit::renderer::IEngineRenderer {
    public:
        ~EngineRenderer() override;
        void get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const override;
    };
} // usr

#endif //ENGINE_RENDERER_HPP
