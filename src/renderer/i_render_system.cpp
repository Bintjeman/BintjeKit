/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_render_system.cpp
 */

#include "bintjekit/renderer/i_render_system.hpp"
#include <SFML/Graphics/View.hpp>
#include "bintjekit/logger.hpp"
namespace bnjkit {
    namespace renderer {
        IRenderSystem::IRenderSystem() {
            m_view = std::make_shared<sf::View>();
            m_logger=core::Logger::get_logger(bnjkit::core::module_names::RENDERER);
        }
        IRenderSystem::~IRenderSystem() = default;
        void IRenderSystem::render(sf::RenderTarget& target[[maybe_unused]]) const {}
        void IRenderSystem::update() {}
        const sf::View& IRenderSystem::view() const {
            return * m_view;
        }
        void IRenderSystem::set_view(const std::shared_ptr<sf::View>& view) {
            m_view = view;
        }
        void IRenderSystem::configure() {}
        std::string IRenderSystem::name() const {
            return "IRenderSystem";
        }
    } // renderer
} // bnjkit
