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
export import bik.settings;
namespace bik::playground {
    export
    /*!
     * @prief Class de base pour la simulation. Elle est un composant de la class Core
     */
    class BasePlayGround : public settings::HasSettings {
    public:
        BasePlayGround();
        ~BasePlayGround() override;

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
    };
}
