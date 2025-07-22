/*!
 * @author bintjeman
 * @date 14.06.25
 * @name common.hpp
 */
#ifndef BNJKIT_CORE_COMMON_HPP
#define BNJKIT_CORE_COMMON_HPP
#pragma once
namespace bnjkit::literals::logger {
    // constexpr auto NONE = "";
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
namespace bnjkit::literals {
    static constexpr auto logger_enum = std::array<std::string, 10>{
        // logger::NONE,
        logger::APP,
        logger::LOG,
        logger::CORE,
        logger::ENGINE,
        logger::RENDERER,
        logger::WINDOW,
        logger::EVENT,
        logger::CONFIGURATION,
        logger::ENTITY,
        logger::ECS
    };
}
#endif // BNJKIT_CORE_COMMON_HPP
