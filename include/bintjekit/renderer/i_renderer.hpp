/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.hpp
 */

#ifndef I_RENDERER_HPP
#define I_RENDERER_HPP
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/engine/i_engine.hpp"

namespace bnjkit {
    namespace renderer {
        class IRenderer : public core::IModule {
        public:
            ~IRenderer() override;
            virtual void render() = 0;
            virtual void renderGUI() =0;
            virtual void set_render_window(sf::RenderWindow *window);
            virtual void set_engine(engine::IEngine *engine);

        protected:
            sf::RenderWindow *m_render_window;
            engine::IEngine *m_engine;
            std::vector<std::reference_wrapper<sf::Drawable> > m_drawables;
        };
    } // renderer
} // bnjkit
#endif //I_RENDERER_HPP
