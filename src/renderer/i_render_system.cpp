/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_render_system.cpp
 */

#include "bintjekit/renderer/i_render_system.hpp"
#include "bintjekit/logger.hpp"

namespace bnjkit::renderer {
    IRenderSystem::IRenderSystem() {
        m_logger = logger::Logger::get_logger(literals::logger::RENDERER);
        m_logger->info("IRenderSystem created");
    }
    IRenderSystem::~IRenderSystem() {
        m_logger->info("IRenderSystem destroyed");
    }
    void IRenderSystem::initialize(engine::IEngine& engine[[maybe_unused]]) {}
    void IRenderSystem::update(engine::IEngine& engine[[maybe_unused]]) {}
    void IRenderSystem::cleanup(engine::IEngine& engine[[maybe_unused]]) {}
    void IRenderSystem::render(sf::RenderTarget& target[[maybe_unused]]) const {}
}
