/*!
 * @author bintjeman
 * @date 13.06.25
 * @name i_engine_renderer.hpp
 */

#ifndef I_ENGINE_RENDERER_HPP
#define I_ENGINE_RENDERER_HPP
#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <spdlog/fwd.h>
#include "bintjekit/core/i_module.hpp"
namespace bnjkit {
    namespace engine {
        class IEngine;
    }

    namespace
    renderer {
        /**
         * @class IEngineRenderer
         * @brief Abstract interface for rendering engine-related drawables.
         *
         * The `IEngineRenderer` class provides an abstract interface for combining an engine with drawable
         * objects that can be rendered. Implementers of this interface are responsible for managing the relationship
         * between a provided engine and drawable entities.
         */
        class IEngineRenderer : public core::IModule{
        public:
            explicit IEngineRenderer();
            virtual ~IEngineRenderer();
            /**
             * @brief Associates an `IEngine` instance with the renderer for managing engine-related drawables.
             *
             * This method sets the engine instance that the renderer relies on to process and
             * render drawable objects related to the engine's state and behavior. The provided
             * engine should implement the `bnjkit::engine::IEngine` interface.
             *
             * @param engine A pointer to the `bnjkit::engine::IEngine` instance to be associated.
             *               This allows the renderer to interact with the engine's functionalities.
             */
            virtual void set_engine(const bnjkit::engine::IEngine *engine);
            /**
             * @brief Retrieves the list of drawable objects associated with the renderer.
             *
             * This method populates the provided list with references to drawable objects
             * from the rendering engine. These drawables are used for display and rendering
             * purposes within the graphics environment.
             *
             * @param drawable_list A reference to a vector that will be populated with references
             *                      to `sf::Drawable` objects currently managed by the renderer.
             *                      The caller can use this list to process or render the objects.
             */
            virtual void get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const;
            [[nodiscard]] virtual sf::Rect<float> get_bounds() const;

        protected:
            const engine::IEngine *m_engine;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // renderer
} // bnjkit
#endif //I_ENGINE_RENDERER_HPP
