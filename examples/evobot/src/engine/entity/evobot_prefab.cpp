/*!
 * @author bintjeman
 * @date 23.07.25
 * @name evobot_prefab.cpp
 */
#include "evobot_prefab.hpp"
#include <bintjekit/engine/i_engine.hpp>
#include "engine/components/components.hpp"

namespace evo::engine::entity {
    EvobotPrefab::EvobotPrefab() {
        initialize();
    }
    void EvobotPrefab::initialize() {
        spawn = [](bnjkit::engine::IEngine& engine) {
            const auto entity = engine.registry().create();
            engine.registry().emplace<comp::EvobotTag>(entity);
            engine.registry().emplace<comp::RadiusComp>(entity);
            engine.registry().emplace<comp::PositionComp>(entity);
            engine.registry().emplace<comp::VelocityComp>(entity);
            engine.registry().emplace<comp::NeedInitializationMark>(entity);
            return entity;
        };
    }
}
