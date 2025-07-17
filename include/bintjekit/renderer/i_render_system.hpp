/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_render_system.hpp
 */

#ifndef BINTJEKIT_RENDERER_I_RENDER_SYSTEM_HPP
#define BINTJEKIT_RENDERER_I_RENDER_SYSTEM_HPP
#pragma once
#include <memory>
#include <spdlog/fwd.h>
#include "bintjekit/ecs/system/i_system.hpp"

namespace sf {
    class RenderTarget;
}
namespace bnjkit::engine {
    class IEngine;
}
namespace bnjkit::renderer {
    class IRenderSystem : public ecs::ISystem {
    public:
        IRenderSystem();
        ~IRenderSystem() override;
        // Implémentation de ISystem
        void initialize(engine::IEngine& engine) override;
        void update(engine::IEngine& engine) override;
        void cleanup(engine::IEngine& engine) override;

        // Méthode pure de rendu
        virtual void render(sf::RenderTarget& target) const;

    protected:
        std::shared_ptr<spdlog::logger> m_logger;
        static unsigned int m_counter;
    };
}
#endif
