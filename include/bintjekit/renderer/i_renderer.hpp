/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.hpp
 */

#ifndef I_RENDERER_HPP
#define I_RENDERER_HPP
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "i_engine_renderer.hpp"
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/engine/i_engine.hpp"

namespace bnjkit {
    namespace renderer {
        class IRenderer : public core::IModule {
        public:
            IRenderer();
            ~IRenderer() override;
            virtual void render();
            virtual void renderGUI();
            virtual void set_render_window(sf::RenderWindow *window);
            virtual void set_engine(engine::IEngine *engine);
            virtual void set_engine_renderer(IEngineRenderer *engine_renderer);

        protected:
            sf::RenderWindow *m_render_window;
            const engine::IEngine *m_engine;
            const renderer::IEngineRenderer *m_engine_renderer;
            std::vector<std::reference_wrapper<sf::Drawable> > m_drawables;
        };
    } // renderer
} // bnjkit
#endif //I_RENDERER_HPP
