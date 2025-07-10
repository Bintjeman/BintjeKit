/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component.hpp
 */

#ifndef BINTJEKIT_ENTITY_COMPONENT_HPP
#define BINTJEKIT_ENTITY_COMPONENT_HPP
#pragma once
#include <type_traits>
namespace bnjkit::entity {
    class IComponent {
    public:
        virtual ~IComponent() = default;
    };

    template<typename T>
    concept is_component = std::is_base_of_v<IComponent, T>;
}
#endif // BINTJEKIT_ENTITY_COMPONENT_HPP
