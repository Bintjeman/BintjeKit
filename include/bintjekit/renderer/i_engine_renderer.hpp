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

    namespace
    renderer {
        enum class RenderLayer {
            Background = 0,
            World = 100,
            Entities = 200,
            Effects = 300,
            Debug = 400,
            UI = 500
        };

        class IRenderSystem;
        class IEngineRenderer : public core::IModule {
        public:
            explicit IEngineRenderer();
            ~IEngineRenderer() override;
            void configure() override;
            virtual void set_engine(const engine::IEngine* engine);
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
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // renderer
} // bnjkit
#endif // BNJKIT_RENDERER_I_ENGINE_RENDERER_HPP
