/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entity.cpp
 */

#include "bintjekit/entity/entity.hpp"

#include <cstddef>

namespace bnjkit {
    namespace entity {
        std::size_t Entity::s_next_id = 0;
        std::size_t Entity::s_total_entities = 0;
        Entity::Entity() {
            m_id = s_next_id;
            s_next_id++;
            s_total_entities++;
        }
        Entity::~Entity() {
            s_total_entities--;
        }
        std::size_t Entity::id() const {
            return m_id;
        }
        std::size_t Entity::next_id() {
            return s_next_id;
        }
        std::size_t Entity::total_entities() {
            return s_total_entities;
        }
    } // entity
} // bnjkit
