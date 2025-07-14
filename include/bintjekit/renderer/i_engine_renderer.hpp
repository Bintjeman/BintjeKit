/*!
 * @author bintjeman
 * @date 13.06.25
 * @name i_engine_renderer.hpp
 */

#ifndef BNJKIT_RENDERER_I_ENGINE_RENDERER_HPP
#define BNJKIT_RENDERER_I_ENGINE_RENDERER_HPP
#pragma once
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include "bintjekit/core/i_module.hpp"

namespace sf {
    class View;
    class RenderTarget;
}

namespace bnjkit {
    namespace engine {
        class IEngine;
    }
}

namespace bnjkit::renderer {
    enum class RenderLayer {
        BACKGROUND = 0,
        WORLD = 100,
        ENTITIES = 200,
        EFFECTS = 300,
        DEBUG = 400,
        UI = 500
    };
    class IRenderSystem;
    class IEngineRenderer : public core::IModule {
    public:
        explicit IEngineRenderer();
        ~IEngineRenderer() override;
        void initialise() override;
        void configure() override;
        virtual void set_engine(const engine::IEngine* engine);
        void set_default_view(const std::shared_ptr<sf::View>& view);
        void set_view(RenderLayer layer, const std::shared_ptr<sf::View>& view);
        void add_render_system(std::unique_ptr<IRenderSystem> system, RenderLayer layer);
        bool remove_render_system(const std::string& name);
        void clear();
        bool toggle_render_system(const std::string& system_name, bool enable);
        void render(sf::RenderTarget& target) const;
        [[nodiscard]] virtual sf::Rect<float> bounds() const;
        [[nodiscard]] std::string name() const override;

    protected:
        struct RenderSystemEntry {
            std::unique_ptr<IRenderSystem> system;
            bool enabled = true;
            std::string name;
        };
        const engine::IEngine* m_engine;
        std::map<RenderLayer, std::vector<RenderSystemEntry> > m_render_systems;
        std::unordered_map<std::string, std::pair<RenderLayer, std::size_t> > m_system_registry;
        std::unordered_map<RenderLayer, std::shared_ptr<sf::View> > m_layer_views;
        std::shared_ptr<sf::View> m_default_view;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#endif // BNJKIT_RENDERER_I_ENGINE_RENDERER_HPP
