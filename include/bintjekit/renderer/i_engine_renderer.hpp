/*!
 * @author bintjeman
 * @date 13.06.25
 * @name i_engine_renderer.hpp
 */

#ifndef BNJKIT_RENDERER_I_ENGINE_RENDERER_HPP
#define BNJKIT_RENDERER_I_ENGINE_RENDERER_HPP
#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "bintjekit/core/i_module.hpp"
namespace bnjkit {
    namespace engine {
        class IEngine;
    }

    namespace
    renderer {
        class IEngineRenderer : public core::IModule{
        public:
            explicit IEngineRenderer();
            ~IEngineRenderer() override;
            virtual void set_engine(const engine::IEngine *engine);
            virtual void get_drawable(std::vector<std::reference_wrapper<sf::Drawable> > &drawable_list) const;
            [[nodiscard]] virtual sf::Rect<float> get_bounds() const;
            [[nodiscard]] std::string name() const override;

        protected:
            const engine::IEngine *m_engine;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // renderer
} // bnjkit
#endif // BNJKIT_RENDERER_I_ENGINE_RENDERER_HPP
