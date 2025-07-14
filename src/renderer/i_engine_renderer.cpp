/*!
 * @author bintjeman
 * @date 13.06.25
 * @name i_engine_renderer.cpp
 */
#include "bintjekit/renderer/i_engine_renderer.hpp"
// #include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/renderer/i_render_system.hpp"

namespace bnjkit::renderer {
    IEngineRenderer::IEngineRenderer(): m_engine(nullptr) {
        m_logger = core::Logger::get_logger(core::module_names::RENDERER);
        m_logger->info("Constructor of IEngineRenderer");
        m_default_view = std::make_shared<sf::View>();
    }

    IEngineRenderer::~IEngineRenderer() {
        m_logger->info("Destructor of IEngineRenderer");
    }
    void IEngineRenderer::initialise() {
        IModule::initialise();
        m_logger->trace("Initialising IEngineRenderer");
        m_layer_views[RenderLayer::BACKGROUND] = m_default_view;
        m_layer_views[RenderLayer::WORLD] = m_default_view;
        m_layer_views[RenderLayer::ENTITIES] = m_default_view;
        m_layer_views[RenderLayer::EFFECTS] = m_default_view;
        m_layer_views[RenderLayer::UI] = m_default_view;
        m_layer_views[RenderLayer::DEBUG] = m_default_view;
    }
    void IEngineRenderer::configure() {
        IModule::configure();
    }
    void IEngineRenderer::set_engine(const engine::IEngine* engine) {
        m_logger->trace("Setting engine");
        m_engine = engine;
    }
    void IEngineRenderer::set_default_view(const std::shared_ptr<sf::View>& view) {
        m_logger->trace("Setting default view");
        m_default_view = view;
    }
    void IEngineRenderer::set_view(RenderLayer layer, const std::shared_ptr<sf::View>& view) {
        m_logger->trace("Setting view for layer {}", render_layer_to_string(layer));
        m_layer_views[layer] = view;
    }
    void IEngineRenderer::add_render_system(std::unique_ptr<IRenderSystem> system, RenderLayer layer) {
        const std::string system_name = system->name();
        m_logger->trace("Adding render system: {}", system_name);
        if (m_render_systems.find(layer) == m_render_systems.end()) {
            m_render_systems[layer] = std::vector<RenderSystemEntry>();
        }
        size_t index = m_render_systems[layer].size();
        m_render_systems[layer].push_back({
            std::move(system),
            true,
            system_name
        });
        m_system_registry[system_name] = {layer, index};
    }
    bool IEngineRenderer::remove_render_system(const std::string& name) {
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
    void IEngineRenderer::clear() {
        m_render_systems.clear();
        m_system_registry.clear();
        m_layer_views.clear();
    }
    bool IEngineRenderer::toggle_render_system(const std::string& system_name, bool enable) {
        auto it = m_system_registry.find(system_name);
        if (it == m_system_registry.end()) {
            m_logger->warn("Système non trouvé : {}", system_name);
            return false;
        }
        auto [layer, index] = it->second;
        m_render_systems[layer][index].enabled = enable;
        m_logger->info("Système {} : {}", system_name, enable ? "activé" : "désactivé");
        return true;
    }
    void IEngineRenderer::render(sf::RenderTarget& target) const {
        for (const auto& [layer, systems]: m_render_systems) {
            target.setView(* m_layer_views.at(layer));
            for (const auto& entry: systems) {
                if (entry.enabled && entry.system) {
                    entry.system->render(target);
                }
            }
        }
    }

    sf::Rect<float> IEngineRenderer::bounds() const {
        m_logger->trace("Getting bounds");
        return {{0.f, 0.f}, {100.f, 100.f}};
    }
    std::string IEngineRenderer::name() const {
        return "IEngineRenderer";
    }
    std::string render_layer_to_string(RenderLayer layer) {
        switch (layer) {
            case RenderLayer::BACKGROUND:
                return "BACKGROUND";
            case RenderLayer::WORLD:
                return "WORLD";
            case RenderLayer::ENTITIES:
                return "ENTITIES";
            case RenderLayer::EFFECTS:
                return "EFFECTS";
            case RenderLayer::UI:
                return "UI";
            case RenderLayer::DEBUG:
                return "DEBUG";
            default:
                return "UNKNOWN";
        }
    }
}
