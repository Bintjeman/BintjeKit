/*!
 * @author bintjeman
 * @date 24.07.25
 * @name render_evobot.hpp
 */

#ifndef RENDER_EVOBOT_HPP
#define RENDER_EVOBOT_HPP
#pragma once
#include <SFML/Graphics/Color.hpp>
#include <bintjekit/renderer/i_render_system.hpp>
namespace bnjkit::engin {
    class IEngine;
}
namespace bnjkit::conf {
    class Node;
}
namespace evo::renderer {
    class EvobotRenderer final : public bnjkit::renderer::IRenderSystem {
    public:
        EvobotRenderer();
        ~EvobotRenderer() override;
        void initialize(bnjkit::engine::IEngine& engine) override;
        void configure(bnjkit::conf::Node settings);
        void render(sf::RenderTarget& target) const override;
        [[nodiscard]] std::string name() const override;

    private:
        bnjkit::engine::IEngine* m_engine{};
        sf::Color m_evobot_color{255, 0, 0, 255};
        sf::Color m_outline_color{255, 255, 255, 255};
    };
}
#endif
