/*!
 * @author bintjeman
 * @date 07.07.25
 * @name EntityManager.hpp
 */
#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
#pragma once
#include <type_traits>
#include "bintjekit/entity/ientity.hpp"
#include "entity_collection.hpp"

namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::is_base_of_v<BaseEntity, IEntity>
    class EntityManager {
    public:
    private:
        EntityCollectionManager<BaseEntity> m_entity_collection_manager;
    };
}
#endif //ENTITYMANAGER_HPP
