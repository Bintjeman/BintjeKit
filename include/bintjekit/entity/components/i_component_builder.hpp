/*!
 * @author bintjeman
 * @date 12.07.25
 * @name i_component_builder.hpp
 */

#ifndef BINTJEKIT_ENTITY_COMPINENTS_I_COMPONENT_BUILDER_HPP
#define BINTJEKIT_ENTITY_COMPINENTS_I_COMPONENT_BUILDER_HPP
#pragma once
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    class IComponentBuilder {
    public:
        virtual ~IComponentBuilder() = default;
        virtual void build(IEntity& entity) = 0;
        virtual void configure() = 0;
    };
}
#endif //BINTJEKIT_ENTITY_COMPINENTS_I_COMPONENT_BUILDER_HPP
