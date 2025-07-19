/*!
 * @author bintjeman
 * @date 15.07.25
 * @name render_system_manager.cpp
 */
#include "bintjekit/renderer/render_system_manager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

#include "bintjekit/renderer/i_render_system.hpp"

namespace bnjkit::renderer {
    RenderSystemManager::RenderSystemManager() {
        m_logger->info("RenderSystemManager created");
    }
    RenderSystemManager::~RenderSystemManager() {
        m_logger->info("RenderSystemManager destroyed");
    }
    void RenderSystemManager::initialise() {
        m_logger->trace("RenderSystemManager: Initializing");
        SystemManager<IRenderSystem, RenderPriority>::initialise();
        m_default_view = nullptr;
        set_all_views(m_default_view);
    }
    void RenderSystemManager::configure() {
        m_logger->trace("RenderSystemManager: Configuring");
        SystemManager<IRenderSystem, RenderPriority>::configure();
    }
    void RenderSystemManager::set_default_view(const std::shared_ptr<sf::View>& view, bool set_all_view) {
        m_default_view = view;
        if (set_all_view) {
            set_all_views(m_default_view);
        }
    }
    void RenderSystemManager::set_view(RenderPriority priority, const std::shared_ptr<sf::View>& view) {
        m_priority_views[priority] = view;
    }
    void RenderSystemManager::render(sf::RenderTarget& target) const {
        for ( const auto& [priority, system]: m_systems ) {
            const auto& view = m_priority_views.at(priority);
            target.setView(* view);
            for (const auto& system_entry: system) {
                if (system_entry.enabled) {
                    system_entry.system->render(target);
                }
            }
        }
    }
    void RenderSystemManager::set_all_views(const std::shared_ptr<sf::View>& view) {
        m_priority_views[RenderLayer::BACKGROUND] = view;
        m_priority_views[RenderLayer::WORLD] = view;
        m_priority_views[RenderLayer::ENTITIES] = view;
        m_priority_views[RenderLayer::DEBUG] = view;
        m_priority_views[RenderLayer::UI] = view;
    }
}
