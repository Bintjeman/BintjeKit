/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.hpp
 */

#ifndef I_RENDERER_HPP
#define I_RENDERER_HPP
#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <spdlog/fwd.h>

#include "i_bnjkit_imgui.hpp"
#include "i_engine_renderer.hpp"
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"

namespace bnjkit {
    namespace renderer {
        /**
         * @class IRenderer
         * @brief Abstract interface for rendering modules.
         *
         * The IRenderer class provides a common interface for rendering modules
         * within the system. It allows rendering a scene and GUI, as well as
         * configuring necessary rendering dependencies such as the render window,
         * engine instance, and engine renderer.
         *
         * It is intended to be subclassed by specific rendering implementations
         * that define the behavior for rendering operations.
         *
         * @note Inherits from core::IModule.
         */
        class IRenderer : public core::IModule, public event::IEventListener {
        public:
            IRenderer();
            ~IRenderer() override;
            void configure() override;
            void render();
            virtual void render_scene();
            virtual void render_gui();
            virtual void set_render_window(sf::RenderWindow *window);
            /**
             * @brief Sets the engine instance for the renderer.
             *
             * This method assigns a specific engine instance to the renderer. The engine
             * serves as the core module responsible for managing the application's state,
             * logic, and other modules. This method must be called to establish the
             * renderer's dependency on the engine before using other functionalities
             * that rely on the engine's state or configuration.
             *
             * @param engine Pointer to the engine::IEngine instance to be used by the renderer.
             */
            virtual void set_engine(engine::IEngine *engine);
            /**
             * @brief Sets the engine renderer for the rendering module.
             *
             * This method assigns the specified engine renderer to the IRenderer
             * instance. The engine renderer is responsible for handling rendering
             * operations and dependencies specific to the application's engine.
             * It must be set before initiating rendering processes to ensure a
             * proper link between the engine and the rendering module.
             *
             * @param engine_renderer Pointer to the renderer::IEngineRenderer instance
             *                        to be associated with the IRenderer.
             */
            virtual void set_engine_renderer(IEngineRenderer *engine_renderer);
            virtual void set_imgui_renderer(IImGuiRenderer *imgui_renderer);

        protected:
            void resize_views();

        public:

        protected:
            void begin_frame();
            void end_frame();
            sf::RenderWindow *m_render_window;
            const engine::IEngine *m_engine;
            const IEngineRenderer *m_engine_renderer;
            IImGuiRenderer *m_imgui_renderer;
            std::vector<std::reference_wrapper<sf::Drawable> > m_drawables;
            sf::View m_engine_view;
            sf::View m_gui_view;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // renderer
} // bnjkit
#endif //I_RENDERER_HPP
