/*!
 * @author bintjeman
 * @date 24.07.25
 * @name ball_init_system.hpp
 */

#ifndef BALL_INIT_SYSTEM_HPP
#define BALL_INIT_SYSTEM_HPP
#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <bintjekit/ecs/system/i_system.hpp>
#include "bintjekit/configuration/node.hpp"

namespace bil {
    class BallInitSystem final : public bnjkit::ecs::ISystem {
    public:
        ~BallInitSystem() override;
        void configuration(bnjkit::engine::IEngine& engine, bnjkit::conf::Node node);
        void update(bnjkit::engine::IEngine& engine) override;
        [[nodiscard]] std::string name() const override;

    private:
        sf::Rect<float> m_bounds{{0.f, 0.f}, {200.f, 200.f}};
        float m_speed_max{0.f};
        float m_radius{10.f};
    };
} // bil

#endif
