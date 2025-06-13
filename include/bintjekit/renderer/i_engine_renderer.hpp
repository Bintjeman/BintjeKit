/*!
 * @author bintjeman
 * @date 13.06.25
 * @name i_engine_renderer.hpp
 */

#ifndef I_ENGINE_RENDERER_HPP
#define I_ENGINE_RENDERER_HPP
#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>

namespace bnjkit {
    namespace engine {
        class IEngine;
    }

    namespace
    renderer {
        class IEngineRenderer {
        public:
            explicit IEngineRenderer();
            virtual ~IEngineRenderer();
            void set_engine(const engine::IEngine *engine);
            virtual void get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const;

        protected:
            const engine::IEngine *m_engine;
        };
    } // renderer
} // bnjkit
#endif //I_ENGINE_RENDERER_HPP
