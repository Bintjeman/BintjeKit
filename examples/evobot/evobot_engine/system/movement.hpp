/*!
 * @author bintjeman
 * @date 13.07.25
 * @name movement.hpp
 */

#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#pragma once
#include "bintjekit/ecs/system/i_system.hpp"

namespace evo::engine {
    class EvoWorld;
}

namespace evo::engine::comp {
    struct D2;
    struct Velocity;
}

namespace evo::engine::systems {
    class Movement final : public bnjkit::engine::ISystem {
    public:
        explicit Movement();
        ~Movement() override;
        void initialize(bnjkit::engine::IEngine& world) override;

        void update(bnjkit::engine::IEngine& world) override;
        void cleanup(bnjkit::engine::IEngine& world) override;

    private:
        void update_position(EvoWorld& evo_world,
                             comp::D2& position,
                             comp::Velocity& velocity);

    public:
        [[nodiscard]] std::string name() const override;
    };
};

#endif //MOVEMENT_HPP
