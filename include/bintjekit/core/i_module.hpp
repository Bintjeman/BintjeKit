/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_module.hpp
 */

#ifndef BINTJEKIT_CORE_I_MODULE_HPP
#define BINTJEKIT_CORE_I_MODULE_HPP
#pragma once
#include "bintjekit/configuration/node.hpp"
namespace bnjkit {
    namespace core {
        class IModule {
        public:
            virtual ~IModule();
            virtual void initialise();
            virtual void configure();
            void set_settings(const conf::Node& settings);
        protected:
            conf::Node m_settings;
        };
    } // core
} // bnjkit
#endif // BINTJEKIT_CORE_I_MODULE_HPP
