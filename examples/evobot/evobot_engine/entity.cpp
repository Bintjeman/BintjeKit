/*!
 * @author bintjeman
 * @date 04.07.25
 * @name entity.cpp
 */

#include "entity.hpp"

namespace evo::engine {
    Entity::Entity(): m_movable({}) {};

    Entity::~Entity() = default;

    void Entity::update() {
        m_movable.update();
    }
    D2::Position Entity::position() const {
        return m_movable.position;
    }
    float Entity::radius() const {
        return m_movable.radius;
    }
    D2::Bounds Entity::bounds() const {
        return m_movable.bounds();
    }
    Movable::Velocity Entity::velocity() const {
        return m_movable.velocity;
    }
    void Entity::set_position(const D2::Position position) {
        m_movable.position = position;
    }
    void Entity::set_radius(const float size) {
        m_movable.radius = size;
    }
    void Entity::set_velocity(const Movable::Velocity velocity) {
        m_movable.velocity = velocity;
    }
}
