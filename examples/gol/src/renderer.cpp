/*!
 * @author bintjeman
 * @date 14.06.25
 * @name renderer.cpp
 */
#include "renderer.hpp"

#include <spdlog/logger.h>

namespace gol {
    Renderer::Renderer() : IRenderer() {
        m_logger->info("Constructor of Renderer");
    }

    void Renderer::on_sfml_event(const sf::Event &event) {
        if (const auto &resized = event.getIf<sf::Event::Resized>()) {
            resize_views();
        }
    }
} // gol
