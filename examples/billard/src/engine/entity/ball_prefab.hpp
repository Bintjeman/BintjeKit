/*!
 * @author bintjeman
 * @date 19.07.25
 * @name ball_prefab.hpp
 */

#ifndef BALL_PREFAB_HPP
#define BALL_PREFAB_HPP
#pragma once

#include <bintjekit/ecs/prefab/prefab.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace bnjkit::conf {
    class Node;
}

namespace bil {
    class Billard;
}

namespace bil {
    class BallPrefab : public bnjkit::ecs::PrefabData {
    public:
        void initialise(const bnjkit::engine::IEngine& engine, bnjkit::conf::Node node);

    private:
        void initialise_spawner();
        sf::Rect<float> m_bounds{{0.f, 0.f}, {200.f, 200.f}};
        float m_speed_max{0.f};
        float m_radius{10.f};
    };
} // bil

#endif //BALL_PREFAB_HPP
