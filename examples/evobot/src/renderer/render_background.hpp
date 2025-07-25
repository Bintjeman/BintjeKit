/*!
 * @author bintjeman
 * @date 23.07.25
 * @name render_back_ground.hpp
 */

#ifndef EVO_RENDERER_RENDER_BACK_GROUND_HPP
#define EVO_RENDERER_RENDER_BACK_GROUND_HPP
#pragma once
#include <bintjekit/renderer/i_render_system.hpp>
#include <SFML/Graphics/Color.hpp>

namespace bnjkit::conf {
    class Node;
}

namespace bnjkit::engine {
    class IEngine;
}

namespace evo::renderer {
    class RenderBackGround final : public bnjkit::renderer::IRenderSystem {
    public:
        RenderBackGround();
        ~RenderBackGround() override;
        void initialize(bnjkit::engine::IEngine& engine) override;
        void configure(bnjkit::conf::Node node);
        void render(sf::RenderTarget& target) const override;
        [[nodiscard]] std::string name() const override;

    private:
        sf::Color m_background_color{20, 100, 10, 100};
        sf::Color m_outline_color{255, 255, 255, 255};
        bnjkit::engine::IEngine* m_engine{};
    };
}
#endif
