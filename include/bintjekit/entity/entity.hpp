/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entity.hpp
 */
#ifndef BINJTJEKIT_ENTITY_ENTITY_HPP
#define BINJTJEKIT_ENTITY_ENTITY_HPP
#pragma once
// #include <cstddef>
#include <limits>

namespace bnjkit {
    namespace entity {
        using EntityId = std::size_t;
        class Entity {
        public:
            Entity();
            virtual ~Entity();
            // Entity(const Entity& other, bool preserve_id = true);
            // Entity& operator=(const Entity& other);
            Entity(const Entity&) = delete;
            Entity(Entity&& other) noexcept;
            Entity& operator=(Entity&& other) noexcept;
            [[nodiscard]] EntityId id() const;
            static EntityId total_entities();

        protected:
            static EntityId next_id();
            EntityId m_id;
            static EntityId s_total_entities;
            static EntityId s_next_id;
            static constexpr EntityId INVALID_ID = std::numeric_limits<EntityId>::max();
        }; // Entity
    } // entity
} // bnjkit

#endif // BINJTJEKIT_ENTITY_ENTITY_HPP
