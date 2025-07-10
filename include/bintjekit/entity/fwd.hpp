/*!
 * @author bintjeman
 * @date 10.07.25
 * @name fwd.hpp
 */

#ifndef BINTJEKIT_ENTITY_FWD_HPP
#define BINTJEKIT_ENTITY_FWD_HPP
#pragma once
#include "ientity.hpp"

namespace bnjkit::entity {
    class EntityCollection;
    template<typename EntityType>
        requires std::is_base_of_v<IEntity, EntityType>
    class TypedCollection;
    template<typename T>
    class ComponentView;
}

#endif // BINTJEKIT_ENTITY_FWD_HPP
