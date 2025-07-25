/*!
 * @author bintjeman
 * @date 23.07.25
 * @name evobot_prefab.hpp
 */

#ifndef EVOBOT_PREFAB_HPP
#define EVOBOT_PREFAB_HPP
#pragma once
#include <bintjekit/ecs/prefab/prefab.hpp>

namespace evo::engine::entity {
    class EvobotPrefab : public bnjkit::ecs::PrefabData {
    public:
        EvobotPrefab();

    private:
        void initialize();
    };
}
#endif
