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
            IModule();
            virtual ~IModule();
            virtual void initialise();
            virtual void configure();
            virtual void on_quit();
            void set_settings(const conf::Node& settings);
            void set_custom(const conf::Node& settings);
            [[nodiscard]] virtual std::string name() const =0;

        protected:
            conf::Node m_settings;
            conf::Node m_custom_settings;
        };
    } // core
} // bnjkit
#endif // BINTJEKIT_CORE_I_MODULE_HPP
