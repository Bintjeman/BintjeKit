/*!
 * @author bintjeman
 * @date 19.07.25
 * @name ball_prefab.cpp
 */
#include "ball_prefab.hpp"
#include "engine/billard.hpp"
#include "engine/components/entity.hpp"
#include "engine/components/position_component.hpp"
#include "engine/components/radius_component.hpp"
#include "engine/components/velocity_compponent.hpp"

namespace bil {
    void BallPrefab::initialise() {
        initialise_spawner();
    }
    void BallPrefab::initialise_spawner() {
        spawn = [*this](bnjkit::engine::IEngine& engine) -> entt::entity {
            auto& registry = engine.registry();
            auto entity = registry.create();
            registry.emplace<components::BallFlag>(entity);
            registry.emplace<components::NeedsInitMark>(entity);
            registry.emplace<components::PositionComponent>(entity);
            registry.emplace<components::RadiusComponent>(entity);
            registry.emplace<components::VelocityComponent>(entity);
            return entity;
        };
    }
}
