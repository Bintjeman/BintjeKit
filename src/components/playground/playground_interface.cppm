/*!
 * @file simulation_interface.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <SFML/Graphics/Rect.hpp>
export module bik.playground:interface;
import bik.settings;
namespace bik::playground {
    export
    /*!
     * @prief Class de base pour la simulation. Elle est un composant de la class Core
     */
    class BasePlayGround {
    public:
        BasePlayGround();
        virtual ~BasePlayGround();

        /*!
         * @brief Définit les paramètres (nlohmann::json avec le wrapper bik::settings) de la simulation.
         *
         * Appelée par core avant void initialize(). Avec un child nomé "Playground".
         *
         * @param settings bik::config::Child qui sera la racine pour les paramètre de la simulation
         */
        virtual void configure(config::Child settings);
        /*!
         * @brief Appelée par Core par default après void configure(config::Child)
         */
        virtual void initialize();
        /*!
         * @brief Appelée à chaque tour par Core
         */
        virtual void update();
        /*!
         * @brief Appelée par Core lors de la fermeture du programme.
         */
        virtual void finalize();
        /*!
         * @brief Utile pour la class BaseRenderer et ses dérivées
         *
         * @return La taille totale du monde simulé
         */
        [[nodiscard]] virtual sf::Rect<float> boundaries() const;

    protected:
        config::Child settings_;
    };
}
