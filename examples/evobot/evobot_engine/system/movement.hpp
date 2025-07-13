/*!
 * @author bintjeman
 * @date 13.07.25
 * @name movement.hpp
 */

#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#pragma once
#include "bintjekit/engine/system/i_system.hpp"

namespace evo::engine {
    class EvoWorld;
}

namespace evo::engine::comp {
    struct D2;
    struct Velocity;
}

namespace engine::systems {
    class Movement final : public bnjkit::engine::ISystem {
    public:
        explicit Movement();
        ~Movement() override;
        void initialize(bnjkit::engine::World& world) override;

        void update(bnjkit::engine::World& world) override;
        void cleanup(bnjkit::engine::World& world) override;

    private:
        void update_position(evo::engine::EvoWorld& evo_world,
                             evo::engine::comp::D2& position,
                             const evo::engine::comp::Velocity& velocity);
    };
};

#endif //MOVEMENT_HPP
