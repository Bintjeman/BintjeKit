/*!
 * @author bintjeman
 * @date 19.07.25
 * @name radius_component.hpp
 */
#ifndef RADIUS_COMPONENT_HPP
#define RADIUS_COMPONENT_HPP
#pragma once
namespace bil::components {
    struct RadiusComponent {
        explicit RadiusComponent(float r = 10.0f) : radius(r) {}
        float radius;
    };
}
#endif //RADIUS_COMPONENT_HPP
