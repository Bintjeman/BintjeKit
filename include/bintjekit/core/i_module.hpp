/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_module.hpp
 */

#ifndef I_MODULE_HPP
#define I_MODULE_HPP
#pragma once
namespace bnjkit::module {
    class IModule {
    public:
        virtual ~IModule() = default;
        virtual void initialise();
        virtual void configure();
    };
} // bnjkit::module
#endif //I_MODULE_HPP
