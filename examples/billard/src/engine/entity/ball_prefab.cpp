/*!
 * @author bintjeman
 * @date 19.07.25
 * @name ball_prefab.cpp
 */
#include "ball_prefab.hpp"
#include <entt/entt.hpp>
#include <SFML/System/Vector2.hpp>
#include <bintjekit/utils/random/random_engine.hpp>
#include "bintjekit/engine/play_ground.hpp"
#include "engine/billard.hpp"
#include "engine/components/entity.hpp"
#include "engine/components/position_component.hpp"
#include "engine/components/radius_component.hpp"

namespace bil {
    void BallPrefab::initialise() {
        spawn = [](bnjkit::engine::IEngine& engine) -> entt::entity {
            auto billard = dynamic_cast<Billard*>(& engine);
            const auto entity = billard->registry().create();
            constexpr float radius = 10.0f;
            const auto billard_bounds = billard->play_ground().bounds();
            const sf::Rect<float> real_bounds = {
                {
                    billard_bounds.position.x + radius,
                    billard_bounds.position.y + radius
                },
                {
                    billard_bounds.position.x + billard_bounds.size.x - radius,
                    billard_bounds.position.y + billard_bounds.size.y - radius
                }
            };
            auto randomposition = [](const sf::Rect<float>& bounds) {
                const float x = bnjkit::utils::random::RandomEngine::get_float(bounds.position.x,
                                                                               bounds.position.x + bounds.size.x);
                const float y = bnjkit::utils::random::RandomEngine::get_float(bounds.position.y,
                                                                               bounds.position.y + bounds.size.y);
                return sf::Vector2f(x, y);
            };
            sf::Vector2f position = randomposition(real_bounds);
            billard->registry().emplace<components::PositionComponent>(entity, position);
            billard->registry().emplace<components::RadiusComponent>(entity, radius);
            billard->registry().emplace<components::BallFlag>(entity);
            return entity;
        };
    };
}
