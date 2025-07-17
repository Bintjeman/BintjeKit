/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.hpp
 */
#ifndef BNJKIT_CORE_CORE_BUILDER_HPP
#define BNJKIT_CORE_CORE_BUILDER_HPP
#pragma once
#include <spdlog/fwd.h>
#include "module_set.hpp"
namespace bnjkit::core {
    class Core;
    class CoreBuilder {
    public:
        CoreBuilder();
        ~CoreBuilder();
        /*!
         *
         * @tparam T Le type hérité d'un des @see @ref requiered_modules "Liste des module requis"
         * par bnjkit::core::Core
         *
         * @return Une référence vers CoreBuilder
         */
        template<typename T>
        CoreBuilder& set() {
            m_modules_tmp.set_module<T>();
            return * this;
        }
        /*!
         *
         * @return Un pointeur vers bnjkit::core::Core construit via les modules sélectionnés
         * avec @ref CoreBuilder::set()
         */
        std::unique_ptr<Core> build();
    private:
        ModuleSet m_modules_tmp;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#endif // BNJKIT_CORE_CORE_BUILDER_HPP
