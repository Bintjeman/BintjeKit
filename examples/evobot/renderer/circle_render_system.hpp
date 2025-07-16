/*!
 * @author bintjeman
 * @date 13.07.25
 * @name circle_render_system.hpp
 */

#ifndef CIRCLE_RENDER_SYSTEM_HPP
#define CIRCLE_RENDER_SYSTEM_HPP
#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <entt/entity/registry.hpp>
#include "bintjekit/renderer/i_render_system.hpp"
namespace evo::renderer {
    class CircleRenderSystem : public bnjkit::renderer::IRenderSystem {
    public:
        ~CircleRenderSystem() override;
        explicit CircleRenderSystem(const entt::registry& registry);
        void render(sf::RenderTarget& target) const override;

    private:
        const entt::registry& m_registry;
    };
}

#endif //CIRCLE_RENDER_SYSTEM_HPP
