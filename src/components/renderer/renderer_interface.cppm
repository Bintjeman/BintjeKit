/*!
 * @file renderer_interface.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
export module bik.renderer:interface;
export import bik.settings;
namespace bik {
    namespace playground {
        export class BasePlayGround;
    }

    namespace common {
        class BaseCoreInfoProvider;
    }
}

namespace bik::renderer {
    /*!
     * @brief BaseRenderer is an abstract class that serves as the foundational renderer interface.
     *
     * @details This class provides the essential rendering operations and management
     *          of graphical resources such as views, targets, and playgrounds.
     *          BaseRenderer is designed to be extended by specific implementations
     *          for different rendering backends or display configurations.
     *
     * @note This interface also incorporates functionality for camera manipulation
     *       and core system integration.
     *
     * @remarks Extending classes must implement all pure virtual methods,
     *          allowing customization of the rendering logic.
     */
    export
    class BaseRenderer : public bik::settings::HasSettings {
    public:
        BaseRenderer();
        ~BaseRenderer() override;

        /*!
         * @brief Appelée par Core à chaque tour
         */
        virtual void update();
        /*!
         * @brief Appelée par core à la fermeture du programme
         */
        virtual void finalize();
        /*!
         * @brief Appelée par Core. Par default dessine sur la BaseWindow ou sa dérivée (sf::RenderTarget target_)
         */
        virtual void draw();
        /*!
         * @brief Définition de la cible sur laquelle sera dessinée la scène à l'appel de void draw()
         * @param target La cible (sf::RenderTarget)
         */
        virtual void set_target(const std::shared_ptr<sf::RenderTarget> &target);
        /*!
         * @brief Définit la simulation/le jeu qui sera dessiner à l'appel de void draw()
         * @param playground La simulation/le jeu à dessiner (dérivé de bik::BasePlayground)
         */
        virtual void set_playground(const std::shared_ptr<playground::BasePlayGround> &playground);
        /*!
         * @brief Définit le core_info_provider qui partage des informations de Core à BaseRenderer
         * @param core_info_provider
         */
        void set_core_info_provider(common::BaseCoreInfoProvider *core_info_provider);
        /*!
         * @brief Wrapper pour sf::Target::SetView()
         * @param view sf::View
         */
        void set_view(sf::View view);
        /*!
         * @brief Déplace la caméra de la vue du playground
         * @param offset
         */
        void camera_move(sf::Vector2f offset);
        /*!
         * @brief Zoom la caméra de la vue du playground
         * @param zoom
         */
        void camera_zoom(float zoom);
        /*!
         * @brief Recentre et ajuste la taille de la sf::View (playground_view_) sur la sf::Target (target_) en fonction des limites définit par bik::BasePlayground ou sa dérivée)
         */
        void reframe();

    protected:
        sf::View main_view_;
        sf::View playground_view_;
        sf::View ui_view_;
        std::shared_ptr<sf::RenderTarget> target_ = nullptr;
        std::shared_ptr<playground::BasePlayGround> playground_ = nullptr;
        common::BaseCoreInfoProvider *core_info_provider_ = nullptr;
    };
}
