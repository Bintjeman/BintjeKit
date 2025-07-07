/*!
 * @author bintjeman
 * @date 15.06.25
 * @name default_renderer.cpp
 */
#include "bintjekit/renderer/default_renderer.hpp"
#include "bintjekit/renderer/i_renderer.hpp"

namespace bnjkit::renderer {
    void DefaultRenderer::on_sfml_event(const sf::Event &event[[maybe_unused]]) {
    }

    void DefaultRenderer::render_scene() {
        IRenderer::render_scene();
    }
    std::string DefaultRenderer::name() const {
        return "DefaultRenderer";
    }
}
