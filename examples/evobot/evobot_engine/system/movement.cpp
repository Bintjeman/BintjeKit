/*!
 * @author bintjeman
 * @date 13.07.25
 * @name movement.cpp
 */
#include "movement.hpp"

#include <bintjekit/engine/play_ground.hpp>
#include "evobot_engine/evo_world.hpp"
#include "evobot_engine/components/base_components.hpp"

namespace evo::engine::systems {
    Movement::Movement() = default;
    Movement::~Movement() = default;
    void Movement::initialize(bnjkit::engine::World& world) {}
    void Movement::update(bnjkit::engine::World& world) {
        auto& evo_world = static_cast<EvoWorld&>(world);
        auto& registry = evo_world.registry();
        auto view = registry.view<comp::D2,
            comp::Velocity>();

        view.each([this, &evo_world](auto& position, auto& velocity) {
            update_position(evo_world, position, velocity);
        });
    }
    void Movement::cleanup(bnjkit::engine::World& world) {}
    void Movement::update_position(EvoWorld& evo_world,
                                   comp::D2& position,
                                   comp::Velocity& velocity) {
        sf::Vector2f new_position = position.position + velocity.value;

        // Obtention des limites du PlayGround
        const auto& playground = evo_world.play_ground();
        const auto bounds = playground.bounds();

        if (new_position.x < bounds.position.x) {
            new_position.x = bounds.position.x;
            velocity.value.x = - velocity.value.x;
        } else if (new_position.x > bounds.position.x + bounds.size.x) {
            new_position.x = bounds.position.x + bounds.size.x;
            velocity.value.x = - velocity.value.x;
        }

        if (new_position.y < bounds.position.y) {
            new_position.y = bounds.position.y;
            velocity.value.y = - velocity.value.y;
        } else if (new_position.y > bounds.position.y + bounds.size.y) {
            new_position.y = bounds.position.y + bounds.size.y;
            velocity.value.y = - velocity.value.y;
        }
        position.position = new_position;
    }
}
