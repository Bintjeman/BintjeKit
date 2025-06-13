/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_module.hpp
 */

#ifndef I_MODULE_HPP
#define I_MODULE_HPP
#pragma once
namespace bnjkit::core {
    /**
     * @class IModule
     * @brief Abstract base class for modules within the system.
     *
     * The IModule class provides a common interface for all system modules,
     * requiring them to implement initialization and configuration methods.
     * It serves as the base for more specialized module classes.
     *
     * Subclasses of IModule must define functionality for the core module behavior.
     */
    class IModule {
    public:
        virtual ~IModule() = default;
        virtual void initialise();
        virtual void configure();
    };
} // bnjkit::module
#endif //I_MODULE_HPP
