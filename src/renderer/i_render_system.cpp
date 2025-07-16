/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_render_system.cpp
 */

#include "bintjekit/renderer/i_render_system.hpp"
namespace bnjkit::renderer {
    IRenderSystem::IRenderSystem()= default;
    IRenderSystem::~IRenderSystem() = default;
    void IRenderSystem::initialize(engine::IEngine& world[[maybe_unused]]) {}
    void IRenderSystem::update(engine::IEngine& world[[maybe_unused]]) {}
    void IRenderSystem::cleanup(engine::IEngine& world[[maybe_unused]]) {}
    void IRenderSystem::render(sf::RenderTarget& target[[maybe_unused]]) const {}
}
