/*!
 * @author bintjeman
 * @date 13.06.25
 * @name i_engine_renderer.cpp
 */
#include "bintjekit/engine/i_engine.hpp""
#include "bintjekit/renderer/i_engine_renderer.hpp"

namespace bnjkit {
    namespace renderer {
        IEngineRenderer::IEngineRenderer() : m_engine(nullptr) {
        }

        void IEngineRenderer::set_engine(const engine::IEngine *engine) {
            m_engine = engine;
        }

        IEngineRenderer::~IEngineRenderer() = default;

        void IEngineRenderer::get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const {
        }
    } // renderer
} // bnjkit
