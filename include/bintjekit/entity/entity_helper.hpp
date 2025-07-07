/*!
 * @author bintjeman
 * @date 07.07.25
 * @name entity_helper.hpp
 */

#ifndef ENTITY_HELPER_HPP
#define ENTITY_HELPER_HPP
#pragma once
#include <unordered_map>
#include <vector>
#include "bintjekit/entity/ientity.hpp"
namespace bnjkit::entity {
    using EntityPtr = std::shared_ptr<IEntity>;
    using EntityId = std::size_t;
    using EntityCollection = std::vector<EntityPtr>;
    using EntityRegistry = std::unordered_map<EntityId, EntityPtr>;

}
#endif //ENTITY_HELPER_HPP
