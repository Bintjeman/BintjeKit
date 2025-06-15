/*!
 * @author bintjeman
 * @date 15.06.25
 * @name default_renderer.cpp
 */
#include "bintjekit/renderer/default_renderer.hpp"
#include <imgui-SFML.h>
#include "bintjekit/renderer/i_renderer.hpp"
namespace bnjkit {
    namespace renderer {
        void DefaultRenderer::on_sfml_event(const sf::Event &event) {
        }

        void DefaultRenderer::render() {
            m_render_window->clear();
            ImGui::SFML::Render(*m_render_window);
            m_render_window->display();
        }
    } // renderer
} // bnjkit
