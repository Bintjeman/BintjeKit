/*!
 * @author bintjeman
 * @date 14.06.25
 * @name common.hpp
 */
#ifndef BNJKIT_CORE_COMMON_HPP
#define BNJKIT_CORE_COMMON_HPP
#pragma once
namespace bnjkit::literals::logger {
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
#endif // BNJKIT_CORE_COMMON_HPP
