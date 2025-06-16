/*!
 * @author bintjeman
 * @date 14.06.25
 * @name renderer.cpp
 */
#include "renderer.hpp"

#include <imgui.h>
#include <spdlog/logger.h>

#include "game_of_life.hpp"
#include "bintjekit/core/core.hpp"

namespace gol {
    Renderer::Renderer() : IRenderer() {
        m_logger->info("Constructor of Renderer");
    }

    void Renderer::on_sfml_event(const sf::Event &event) {
        if (const auto &resized = event.getIf<sf::Event::Resized>()) {
            resize_views();
        }
    }

    void Renderer::render_gui() {
        ImGui::Begin("Informations");
        ImGui::Text("Core state: %s", bnjkit::core::Core::state_to_string(m_core->state()).c_str());
        ImGui::Text("Gol state: %s", GameOfLife::state_to_string(m_gol->state()).c_str());
        ImGui::End();
    }

    void Renderer::set_engine(const bnjkit::engine::IEngine *engine) {
        m_logger->info("Setting engine");
        IRenderer::set_engine(engine);
        m_gol = dynamic_cast<const GameOfLife *>(engine);
    }
} // gol
