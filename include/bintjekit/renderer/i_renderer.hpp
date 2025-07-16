/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.hpp
 */

#ifndef BNJKIT_RENDERER_I_RENDERER_HPP
#define BNJKIT_RENDERER_I_RENDERER_HPP
#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <spdlog/fwd.h>
#include "i_bnjkit_imgui.hpp"
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"
#include "render_system_manager.hpp"

namespace bnjkit::core {
    class Core;
}
namespace bnjkit::engine {
    class IWorld;
}
namespace bnjkit::renderer {
    class IRenderer : public core::IModule, public event::IEventListener {
    public:
        IRenderer();
        ~IRenderer() override;

        void configure() override;
        void render();
        void resize_views();

        // Gestion des systèmes de rendu
        void add_render_system(std::unique_ptr<IRenderSystem> system, RenderLayer layer);
        bool remove_render_system(const std::string& name);
        bool toggle_render_system(const std::string& name, bool enable);

        // Configuration
        virtual void set_render_window(sf::RenderWindow* window);
        virtual void set_imgui_renderer(IImGuiRenderer* imgui_renderer);
        virtual void set_engine(const ecs::IEngine* engine);
        virtual void set_core(core::Core* core);

        [[nodiscard]] std::string name() const override;

    protected:
        void begin_frame() const;
        void end_frame() const;
        virtual void render_scene();
        virtual void render_gui();
        //
        RenderSystemManager m_render_manager;
        // bnjkit Modules
        sf::RenderWindow* m_render_window;
        IImGuiRenderer* m_imgui_renderer;
        core::Core* m_core;
        const engine::IWorld* m_world;
        // Utils
        std::shared_ptr<sf::View> m_gui_view;
        std::shared_ptr<sf::View> m_world_view;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#endif // BNJKIT_RENDERER_I_RENDERER_HPP
