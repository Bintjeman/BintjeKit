/*!
 * @author bintjeman
 * @date 19.07.25
 * @name ball_prefab.cpp
 */
#include "ball_prefab.hpp"
#include <entt/entt.hpp>
#include <SFML/System/Vector2.hpp>
#include <bintjekit/utils/random/random_engine.hpp>
#include <bintjekit/configuration/node.hpp>
#include "bintjekit/engine/play_ground.hpp"
#include "bintjekit/utils/d2/d2.hpp"
#include "engine/billard.hpp"
#include "engine/components/entity.hpp"
#include "engine/components/position_component.hpp"
#include "engine/components/radius_component.hpp"
#include "engine/components/velocity_compponent.hpp"

namespace bil {
    void BallPrefab::initialise() {
        spawn = [this](bnjkit::engine::IEngine& engine) -> entt::entity {
            const auto billard = dynamic_cast<Billard*>(&engine);
            const auto entity = billard->registry().create();
            auto randomposition = [](const sf::Rect<float>& bounds) {
                const float x = bnjkit::utils::random::RandomEngine::get_float(bounds.position.x,
                                                                               bounds.position.x + bounds.size.x
                );
                const float y = bnjkit::utils::random::RandomEngine::get_float(bounds.position.y,
                                                                               bounds.position.y + bounds.size.y
                );
                return sf::Vector2f(x, y);
            };
            sf::Vector2f position = randomposition(m_bounds);
            billard->registry().emplace<components::PositionComponent>(entity, position);
            billard->registry().emplace<components::RadiusComponent>(entity, m_radius);
            billard->registry().emplace<components::BallFlag>(entity);
            if (m_speed_max > 0.0f) {
                auto angle = []() {
                    return bnjkit::utils::random::RandomEngine::get_float(
                        0.0f,
                        bnjkit::utils::d2::PIX2 - std::numeric_limits<float>::epsilon()
                    );
                };
                auto speed = [m_speed_max = m_speed_max]() {
                    return bnjkit::utils::random::RandomEngine::get_float(0.0f, m_speed_max);
                };
                auto velocity = [angle, speed]() {
                    auto speed_ = speed();
                    return sf::Vector2f(std::cos(angle() * speed_), std::sin(angle() * speed_));
                };
                billard->registry().emplace<components::VelocityComponent>(entity, velocity());
            }
            return entity;
        };
    }

    void BallPrefab::initialise(const bnjkit::engine::IEngine& engine, bnjkit::conf::Node node) {
        const auto billard = dynamic_cast<const Billard*>(&engine);
        m_radius = node.get_or_set("/Radius", 10.0f);
        m_speed_max = node.get_or_set("/SpeedMax", 2.0f);
        const auto billard_bounds = billard->play_ground().bounds();
        m_bounds = {
            {
                billard_bounds.position.x + m_radius,
                billard_bounds.position.y + m_radius
            },
            {
                billard_bounds.size.x - m_radius * 2.f,
                billard_bounds.size.y - m_radius * 2.f
            }
        };
        initialise();
    }
}
