/*!
 * @author bintjeman
 * @date 15.07.25
 * @name render_system_manager.hpp
 */

#ifndef BINTJEKIT_RENDERER_RENDER_SYSTEM_MANAGER_HPP
#define BINTJEKIT_RENDERER_RENDER_SYSTEM_MANAGER_HPP
#pragma once
#include "bintjekit/ecs/i_system_manager.hpp"
#include <array>

namespace sf {
    class RenderTarget;
    class View;
}
namespace bnjkit::renderer {
    class IRenderSystem;
    enum class RenderPriority {
        BACKGROUND = 0,
        WORLD = 100,
        ENTITIES = 200,
        EFFECTS = 300,
        DEBUG = 400,
        UI = 500
    };
    static constexpr std::array<RenderPriority, 6> RENDER_PRIORITIES = {
        RenderPriority::BACKGROUND,
        RenderPriority::WORLD,
        RenderPriority::ENTITIES,
        RenderPriority::EFFECTS,
        RenderPriority::DEBUG,
        RenderPriority::UI
    };
    constexpr auto begin(RenderPriority) { return RENDER_PRIORITIES.begin(); }
    constexpr auto end(RenderPriority) { return RENDER_PRIORITIES.end(); }

    using RenderLayer = RenderPriority;
    class RenderSystemManager : public ecs::SystemManager<IRenderSystem, RenderPriority> {
    public:
        RenderSystemManager();
        ~RenderSystemManager() override;
        void initialise() override;
        void configure() override;
        // Méthodes spécifiques au rendu
        void set_default_view(const std::shared_ptr<sf::View>& view, bool set_all_view);
        void set_view(RenderPriority priority, const std::shared_ptr<sf::View>& view);
        void render(sf::RenderTarget& target) const;

    private:
        void set_all_views(const std::shared_ptr<sf::View>& view = nullptr);
        std::unordered_map<RenderPriority, std::shared_ptr<sf::View>> m_priority_views;
        std::shared_ptr<sf::View> m_default_view;
    };
}

#endif // BINTJEKIT_RENDERER_RENDER_SYSTEM_MANAGER_HPP
