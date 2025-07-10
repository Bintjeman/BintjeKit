/*!
 * @author bintjeman
 * @date 04.07.25
 * @name entity.hpp
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once
#include <bintjekit/entity/ientity.hpp>
#include "evobot_engine/components/d2.hpp"

namespace evo {
    namespace engine {
        class Entity : public bnjkit::entity::IEntity {
        public:
            Entity();
            ~Entity() override;
            void update() override;
            [[nodiscard]] D2::Position position() const;
            [[nodiscard]] float radius() const;
            [[nodiscard]] D2::Bounds bounds() const;
            Movable::Velocity velocity();
            void set_position(D2::Position position);
            void set_radius(float size);
            void set_velocity(Movable::Velocity velocity);
        protected:
            Movable m_movable;

        private:
        };
    } // engine
} // evo

#endif //ENTITY_HPP
