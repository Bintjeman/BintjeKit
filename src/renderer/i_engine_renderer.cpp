/*!
 * @author bintjeman
 * @date 13.06.25
 * @name i_engine_renderer.cpp
 */
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/renderer/i_engine_renderer.hpp"

namespace bnjkit::renderer {
    IEngineRenderer::IEngineRenderer() : m_engine(nullptr) {
        m_logger = core::Logger::get_logger(core::module_names::RENDERER);
        m_logger->info("Constructor of IEngineRenderer");
    }

    void IEngineRenderer::set_engine(const bnjkit::engine::IEngine *engine) {
        m_logger->debug("Setting engine");
        m_engine = engine;
    }

    IEngineRenderer::~IEngineRenderer() {
        m_logger->info("Destructor of IEngineRenderer");
    }

    void IEngineRenderer::get_drawable(
        std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list [[maybe_unused]]) const {
    }

    sf::Rect<float> IEngineRenderer::get_bounds() const {
        m_logger->trace("Getting bounds");
        return {{0.f, 0.f}, {100.f, 100.f}};
    }
    std::string IEngineRenderer::name() const {
        return "IEngineRenderer";
    }
}
