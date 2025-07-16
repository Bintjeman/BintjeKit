/*!
 * @author bintjeman
 * @date 16.07.25
 * @name i_system_manager.cpp
 */
#include "bintjekit/ecs/i_system_manager.hpp"

namespace bnjkit::ecs {
    RenderSystemManager::RenderSystemManager() {
        m_logger = bnjkit::core::Logger::get_logger(bnjkit::core::module_names::RENDERER);
        m_logger->info("RenderSystemManager created");
    }
    RenderSystemManager::~RenderSystemManager() {
        m_logger->info("RenderSystemManager destroyed");
    }
    void RenderSystemManager::initialise() {
        m_logger->trace("RenderSystemManager: Initializing");
        m_default_view = nullptr;
    }
    void RenderSystemManager::configure() {}
    void RenderSystemManager::add_render_system(std::unique_ptr<IRenderSystem> system, RenderLayer layer) {
        m_logger->trace("RenderSystemManager: Adding render system");
        const std::string system_name = system->name();
        m_logger->trace("Adding render system: {}", system_name);
        if (m_render_systems.find(layer) == m_render_systems.end()) {
            m_render_systems[layer] = std::vector<RenderSystemEntry>();
        }
        size_t index = m_render_systems[layer].size();
        m_render_systems[layer].push_back({
            std::move(system),
            system_name,
            true
        });
        m_system_registry[system_name] = {layer, index};
    }
    bool RenderSystemManager::remove_render_system(const std::string& name) {
        auto it = m_system_registry.find(name);
        if (it == m_system_registry.end()) {
            m_logger->warn("Tentative de suppression d'un système inexistant : {}", name);
            return false;
        }
        auto [layer, index] = it->second;
        auto& systems = m_render_systems[layer];
        if (index >= systems.size()) {
            m_logger->error("Index invalide pour le système : {}", name);
            return false;
        }
        // Suppression du système
        systems.erase(systems.begin() + static_cast<std::ptrdiff_t>(index));
        m_system_registry.erase(it);
        // Mise à jour des indices dans le registre
        for (auto& [name_, location]: m_system_registry) {
            if (location.first == layer && location.second > index) {
                location.second--;
            }
        }
        if (m_render_systems[layer].empty()) {
            m_layer_views.erase(layer);
        }
        m_logger->info("Système de rendu supprimé : {}", name);
        return true;
    }
    void RenderSystemManager::clear() {
        m_render_systems.clear();
        m_system_registry.clear();
        m_layer_views.clear();
    }
    void RenderSystemManager::toggle_render_system(const std::string& system_name, bool enable) {
        auto index = m_system_registry[system_name];
        auto system& = m_render_systems[index.first][index.second].enabled = enable;
    }
    void RenderSystemManager::set_default_view(const std::shared_ptr<sf::View>& view) {
        m_default_view = view;
    }
    void RenderSystemManager::set_view(RenderLayer layer, const std::shared_ptr<sf::View>& view) {
        m_layer_views[layer] = view;
    }
    void RenderSystemManager::render(sf::RenderTarget& target) const {
        for (const auto& layer: m_layer_views) {
            target.setView(* layer.second);
            for (const auto& system: layer.first) {
                if (system.enabled && system.system) {
                    system.system->render(target);
                }
            }
        }
    }
    RenderSystemManager::RenderSystemEntry::RenderSystemEntry(std::unique_ptr<IRenderSystem> system, std::string name,
                                                              bool enabled) : system(std::move(system)),
                                                                              name(std::move(name)), enabled(enabled) {}
}
