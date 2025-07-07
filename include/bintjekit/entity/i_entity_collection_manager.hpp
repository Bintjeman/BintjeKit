/*!
 * @author bintjeman
 * @date 07.07.25
 * @name i_entity_collection_manager.hpp
 */

#ifndef I_ENTITY_COLLECTION_MANAGER_HPP
#define I_ENTITY_COLLECTION_MANAGER_HPP
#pragma once
#include "bintjekit/entity/entity_helper.hpp"
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    class IEntityCollectionManager {
    public:
        virtual ~IEntityCollectionManager() = default;
        virtual EntityCollection get_entities() = 0;
        virtual void clear() = 0;
        virtual void remove(EntityId id) = 0;
    };
}
#endif // I_ENTITY_COLLECTION_MANAGER_HPP