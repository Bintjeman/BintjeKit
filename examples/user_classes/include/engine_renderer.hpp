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
    class Engine;

    class EngineRenderer : public bnjkit::renderer::IEngineRenderer {
    public:
        ~EngineRenderer() override;
        void get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const override;
        void set_engine(const bnjkit::engine::IEngine *engine) override;

    private:
        const usr::Engine *m_usr_engine;
    };
} // usr

#endif //ENGINE_RENDERER_HPP
