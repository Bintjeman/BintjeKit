/*!
 * @author bintjeman
 * @date 19.07.25
 * @name background_renderer.cpp
 */
#include "background_renderer.hpp"
#include <spdlog/spdlog.h>
namespace bil {
    BackgroundRenderer::BackgroundRenderer() {
        m_logger->info("BackgroundRenderer created");
    }
    BackgroundRenderer::~BackgroundRenderer() {
        m_logger->info("BackgroundRenderer destroyed");
    }
    void BackgroundRenderer::initialize(bnjkit::engine::IEngine& engine) {
        IRenderSystem::initialize(engine);

    }
    void BackgroundRenderer::update(bnjkit::engine::IEngine& engine) {
        IRenderSystem::update(engine);
    }
    void BackgroundRenderer::render(sf::RenderTarget& target) const {
        // IRenderSystem::render(target);
    }
    std::string BackgroundRenderer::name() const {
        return "BackgroundRenderer";
    }
} // bil