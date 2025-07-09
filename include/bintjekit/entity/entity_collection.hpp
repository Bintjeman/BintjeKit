/*!
 * @author bintjeman
 * @date 08.07.25
 * @name entity_collection.hpp
 */

#ifndef ENTITY_COLLECTION_HPP
#define ENTITY_COLLECTION_HPP
#pragma once
#include <memory>
#include <vector>

#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    class EntityCollection {
    private:
        std::vector<std::shared_ptr<IEntity> > m_entities;
    };
}

#endif //ENTITY_COLLECTION_HPP
