/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entity_helper.hpp
 */

#ifndef ENTITY_HELPER_HPP
#define ENTITY_HELPER_HPP
#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "bintjekit/entity/entity.hpp"

namespace bnjkit {
    namespace entity {
        using EntityPtr = std::shared_ptr<Entity>;
        using EntityCollection = std::vector<EntityPtr>;
        using EntityIndex = std::size_t;
        using EntityRegystry = std::unordered_map<EntityId, EntityIndex>;
    } // entity
} // bnjkit
#endif //ENTITY_HELPER_HPP
