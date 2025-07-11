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

namespace bnjkit {
    namespace engine {
        class IEngine;
    }

    namespace core {
        class Core;
    }

    namespace window {
        class IMainWindow;
    }

    namespace renderer {
        class IEngineRenderer;

        class IRenderer : public core::IModule, public event::IEventListener {
        public:
            IRenderer();
            ~IRenderer() override;
            void configure() override;
            void render();
            void resize_views();
            virtual void render_scene();
            virtual void render_gui();
            virtual void set_render_window(sf::RenderWindow *window);
            virtual void set_imgui_renderer(IImGuiRenderer *imgui_renderer);
            virtual void set_engine(const engine::IEngine *engine);
            virtual void set_engine_renderer(const IEngineRenderer *engine_renderer);
            virtual void set_core(core::Core *core);

        protected:
            void begin_frame() const;
            void end_frame() const;

        public:
            [[nodiscard]] std::string name() const override;

        protected:
            sf::RenderWindow *m_render_window;
            IImGuiRenderer *m_imgui_renderer;
            const engine::IEngine *m_engine;
            const IEngineRenderer *m_engine_renderer;
            core::Core *m_core;
            std::vector<std::reference_wrapper<sf::Drawable> > m_drawables;
            sf::View m_engine_view;
            sf::View m_gui_view;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // renderer
} // bnjkit
#endif // BNJKIT_RENDERER_I_RENDERER_HPP
