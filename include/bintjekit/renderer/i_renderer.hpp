/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.hpp
 */

#ifndef I_RENDERER_HPP
#define I_RENDERER_HPP
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

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
            /**
             * @brief Renders the main scene.
             *
             * This virtual method is responsible for rendering the primary scene
             * visualization. Subclasses of IRenderer should implement the method
             * to define the specific rendering behavior. Typically invoked in the
             * main rendering loop to continuously update visuals within the application.
             */
            virtual void render();
            /**
             * @brief Renders the GUI elements.
             *
             * This virtual method is responsible for rendering the graphical user
             * interface (GUI) components on the screen. It should be implemented
             * by specific renderer subclasses to define the precise behavior of
             * GUI rendering. Typically invoked within the rendering loop to update
             * and display UI components alongside the main scene.
             */
            virtual void renderGUI();
            /**
             * @brief Sets the render window for the renderer.
             *
             * This method assigns the specified render window to the renderer. The render
             * window serves as the target for all rendering operations performed by the
             * renderer. It must be called before rendering operations are initiated to
             * ensure proper display output.
             *
             * @param window Pointer to the sf::RenderWindow that serves as the rendering target.
             */
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

        protected:
            void resize_views();

        public:


        protected:
            sf::RenderWindow *m_render_window;
            const engine::IEngine *m_engine;
            const IEngineRenderer *m_engine_renderer;
            std::vector<std::reference_wrapper<sf::Drawable> > m_drawables;
            sf::View m_engine_view;
            sf::View m_gui_view;
        };
    } // renderer
} // bnjkit
#endif //I_RENDERER_HPP
