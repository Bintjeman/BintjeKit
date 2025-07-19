/*!
 * @author bintjeman
 * @date 19.07.25
 * @name background_renderer.cpp
 */
#include "background_renderer.hpp"
#include <spdlog/spdlog.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include "bintjekit/engine/play_ground.hpp"
#include "engine/billard.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

namespace bil {
    BackgroundRenderer::BackgroundRenderer() : m_engine(nullptr) {
        m_logger->info("BackgroundRenderer created");
    }
    BackgroundRenderer::~BackgroundRenderer() {
        m_logger->info("BackgroundRenderer destroyed");
    }
    void BackgroundRenderer::initialize(bnjkit::engine::IEngine& engine) {
        IRenderSystem::initialize(engine);
        m_engine = dynamic_cast<bil::Billard*>(& engine);
    }
    void BackgroundRenderer::update(bnjkit::engine::IEngine& engine) {
        IRenderSystem::update(engine);
    }
    void BackgroundRenderer::render(sf::RenderTarget& target) const {
        const auto& bounds = m_engine->play_ground().bounds();
        static sf::RectangleShape background;
        static sf::Color color = sf::Color(54,89,74);
        background.setSize(bounds.size);
        background.setPosition(bounds.position);
        background.setFillColor(color);
        target.draw(background);
    }
    std::string BackgroundRenderer::name() const {
        return "BackgroundRenderer";
    }
} // bil
