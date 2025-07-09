/*!
 * @author bintjeman
 * @date 01.07.25
 * @name renderer.cpp
 */

#include "renderer.hpp"
#include <spdlog/logger.h>
#include "evobot_engine/evobot_engine.hpp"

namespace evo {
    namespace renderer {

        void Renderer::configure() {
            bnjkit::renderer::IRenderer::configure();
        }
        std::string Renderer::name() const {
            return "Renderer";
        }
        void Renderer::camera_move(sf::Vector2f delta) {
            m_engine_view.move(delta);
        }
        void Renderer::camera_zoom(float ratio) {
            m_engine_view.zoom(ratio);
        }
        void Renderer::set_engine(const bnjkit::engine::IEngine* engine) {
            IRenderer::set_engine(engine);
            m_evobot = dynamic_cast<const engine::EvobotEngine*>(engine);
        }
    } // renderer
} // evo
