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

        void IEngineRenderer::set_engine(const bnjkit::engine::IEngine *engine) {
            m_engine = engine;
        }

        IEngineRenderer::~IEngineRenderer() = default;

        void IEngineRenderer::get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const {
        }

        sf::Rect<float> IEngineRenderer::get_bounds() const {
            return {{0.f, 0.f}, {100.f, 100.f}};
        }
    } // renderer
} // bnjkit
