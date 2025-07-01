/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entity.hpp
 */
#ifndef BINJTJEKIT_ENTITY_ENTITY_HPP
#define BINJTJEKIT_ENTITY_ENTITY_HPP
#pragma once
#include <cstddef>
namespace bnjkit {
    namespace entity {
        using EntityId = std::size_t;
        class Entity {
        public:
            Entity();
            virtual ~Entity();
            [[nodiscard]] EntityId id() const;
            static EntityId next_id();
            static EntityId total_entities();

        private:
            EntityId m_id;
            static EntityId s_total_entities;
            static EntityId s_next_id;
        }; // Entity
    } // entity
} // bnjkit

#endif // BINJTJEKIT_ENTITY_ENTITY_HPP
