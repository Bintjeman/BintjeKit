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
#include "bintjekit/core/i_module.hpp"
#include "render_system_manager.hpp"

namespace bnjkit::core {
    class ModuleSet;
}

namespace bnjkit::renderer {
    class IRenderer : public core::IModule {
    public:
        IRenderer();
        ~IRenderer() override;
        void initialise() override;
        void configure() override;
        void set_modules(core::ModuleSet* modules);
        void render();
        void resize_views();
        // Gestion des systèmes de rendu
        void add_render_system(std::unique_ptr<IRenderSystem> system, RenderLayer layer);
        void remove_render_system(const std::string& name);
        void toggle_render_system(const std::string& name, bool enable);
        // utils
        [[nodiscard]] std::string name() const override;
        // Views
        [[nodiscard]] sf::View& engine_view();
        [[nodiscard]] const sf::View& engine_view() const;
    protected:
        void begin_frame() const;
        void end_frame() const;
        virtual void render_scene();
        virtual void render_gui();
        //
        RenderSystemManager m_render_system_manager;
        // Utils
        std::shared_ptr<sf::View> m_gui_view;
        std::shared_ptr<sf::View> m_world_view;
        // bnjkit Modules
        core::ModuleSet* m_modules;
    };
}
#endif // BNJKIT_RENDERER_I_RENDERER_HPP
