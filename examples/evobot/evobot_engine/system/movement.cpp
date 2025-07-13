/*!
 * @author bintjeman
 * @date 13.07.25
 * @name movement.cpp
 */
#include "movement.hpp"

#include <bintjekit/engine/play_ground.hpp>
#include "evobot_engine/evo_world.hpp"
#include "evobot_engine/components/base_components.hpp"

namespace engine::systems {
    Movement::Movement() = default;
    Movement::~Movement() = default;
    void Movement::initialize(bnjkit::engine::World& world) {}
    void Movement::update(bnjkit::engine::World& world) {
        auto& evo_world = static_cast<evo::engine::EvoWorld&>(world);
        auto& registry = evo_world.registry();
        auto view = registry.view<evo::engine::comp::D2,
            evo::engine::comp::Velocity>();

        view.each([this, &evo_world](auto& position, const auto& velocity) {
            update_position(evo_world, position, velocity);
        });
    }
    void Movement::cleanup(bnjkit::engine::World& world) {}
    void Movement::update_position(evo::engine::EvoWorld& evo_world,
                                   evo::engine::comp::D2& position,
                                   const evo::engine::comp::Velocity& velocity) {
        sf::Vector2f new_position = position.position + velocity.value;

        // Obtention des limites du PlayGround
        const auto& playground = evo_world.play_ground();
        const auto bounds = playground.bounds();

        // Application du wrap-around ou rebond selon les besoins
        if (new_position.x < bounds.position.x) {
            new_position.x = bounds.position.x;
        } else if (new_position.x > bounds.position.x + bounds.size.x) {
            new_position.x = bounds.position.x + bounds.size.x;
        }

        if (new_position.y < bounds.position.y) {
            new_position.y = bounds.position.y;
        } else if (new_position.y > bounds.position.y + bounds.position.y) {
            new_position.y = bounds.position.y + bounds.size.y;
        }

        position.position = new_position;
    }
}
