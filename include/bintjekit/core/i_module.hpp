/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_module.hpp
 */

#ifndef BINTJEKIT_CORE_I_MODULE_HPP
#define BINTJEKIT_CORE_I_MODULE_HPP
#pragma once
#include "bintjekit/configuration/node.hpp"
#include <spdlog/fwd.h>
#include <memory>
namespace bnjkit::core {
    /*!
     * Class interface pour tous les modules
     */
    class IModule {
    public:
        IModule();
        virtual ~IModule();
        /*!
         * Appelé juste après le constructeur
         */
        virtual void initialise();
        /*!
         * Configure les données et les membres avec le @ref bnjkit::conf::Node
         *
         * @see bnjkit::conf
         */
        virtual void configure();
        /*!
         * Appelé avant le desctructeur
         */
        virtual void on_quit();
        /*!
         *
         * @param settings Configure avec des données choisies
         * @param custom_settings Prépare un noeud json pour les types hérités
         */
        void configure(const conf::Node& settings, const conf::Node& custom_settings = conf::Node());
        void set_settings(const conf::Node& settings);
        /*!
         * Permet d'avoir un deuxième jeu de donnée avec un autre pointeur.
         *
         * @param settings Configure custom_settings avec les données en paramètres
         */
        void set_custom(const conf::Node& settings);
        [[nodiscard]] virtual std::string name() const =0;

    protected:
        conf::Node m_settings; //< Les données pour configurer l'interface du module
        conf::Node m_custom_settings; //< Les données pour configurer le type hérité
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#endif // BINTJEKIT_CORE_I_MODULE_HPP
