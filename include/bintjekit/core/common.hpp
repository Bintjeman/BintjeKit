/*!
 * @author bintjeman
 * @date 14.06.25
 * @name common.hpp
 */

#ifndef BNJKIT_CORE_COMMON_HPP
#define BNJKIT_CORE_COMMON_HPP
#pragma once
namespace bnjkit {
    namespace core {
        namespace module_names {
            constexpr const char* NONE = "";
            constexpr const char* APP = "APP";
            constexpr const char* LOG = "LOG";
            constexpr const char* CORE = "CORE";
            constexpr const char* ENGINE = "ENGINE";
            constexpr const char* RENDERER = "RENDERER";
            constexpr const char* WINDOW = "WINDOW";
            constexpr const char* EVENT = "EVENT";
            constexpr const char* CONFIGURATION = "CONF";
        }
    } // core
} // bnjkit
#endif // BNJKIT_CORE_COMMON_HPP
