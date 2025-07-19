/*!
 * @author bintjeman
 * @date 19.07.25
 * @name ball_prefab.hpp
 */

#ifndef BALL_PREFAB_HPP
#define BALL_PREFAB_HPP
#pragma once

#include <bintjekit/ecs/prefab/prefab.hpp>

namespace bil {
    class Billard;
}

namespace bil {
    class BallPrefab : public bnjkit::ecs::PrefabData {
        public:
        void initialise();

    public:
    };
} // bil

#endif //BALL_PREFAB_HPP
