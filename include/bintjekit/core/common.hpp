/*!
 * @author bintjeman
 * @date 14.06.25
 * @name common.hpp
 */
#ifndef BNJKIT_CORE_COMMON_HPP
#define BNJKIT_CORE_COMMON_HPP
#pragma once
namespace bnjkit::core::module_names {
    constexpr auto NONE = "";
    constexpr auto APP = "APP";
    constexpr auto LOG = "LOG";
    constexpr auto CORE = "CORE";
    constexpr auto ENGINE = "ENGINE";
    constexpr auto RENDERER = "RENDERER";
    constexpr auto WINDOW = "WINDOW";
    constexpr auto EVENT = "EVENT";
    constexpr auto CONFIGURATION = "CONF";
    constexpr auto ENTITY = "ENTITY";
    constexpr auto ECS = "ECS";
}
namespace bnjkit::core {
    static const char* ENUM_MODULE[] = {
        module_names::NONE,
        module_names::APP,
        module_names::LOG,
        module_names::CORE,
        module_names::ENGINE,
        module_names::RENDERER,
        module_names::WINDOW,
        module_names::EVENT,
        module_names::CONFIGURATION,
        module_names::ENTITY,
        module_names::ECS,
    };
}
#endif // BNJKIT_CORE_COMMON_HPP
