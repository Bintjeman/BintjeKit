/*!
 * @author bintjeman
 * @date 16.07.25
 * @name module_set.hpp
 */
#ifndef BINTJEKIT_CORE_MODULE_SET_HPP
#define BINTJEKIT_CORE_MODULE_SET_HPP
#pragma once
#include "bintjekit/core/i_module.hpp"
namespace bnjkit {
    namespace window {
        class IMainWindow;
    }
    namespace event {
        class IEventManager;
    }
    namespace engine {
        class IEngine;
    }
    namespace renderer {
        class IRenderer;
        class IImGuiRenderer;
    }
}

namespace bnjkit::core {
    /*!
     * Enemble de modules requis par la class @see @ref cnjkit::core::Core et partagés par les autres modules
     */
    class ModuleSet {
    public:
        ModuleSet();
        ~ModuleSet();
        // Getters modules
        template<typename T> requires std::is_base_of_v<IModule, T>
        T& get();
        template<typename T> requires std::is_base_of_v<IModule, T>
        const T& get() const;
        // Getter modules
        window::IMainWindow& window();
        event::IEventManager& event_manager();
        engine::IEngine& engine();
        renderer::IRenderer& renderer();
        renderer::IImGuiRenderer& imgui_renderer();
        // Getter modules const
        [[nodiscard]] window::IMainWindow& window() const;
        [[nodiscard]] event::IEventManager& event_manager() const;
        [[nodiscard]] engine::IEngine& engine() const;
        [[nodiscard]] renderer::IRenderer& renderer() const;
        [[nodiscard]] renderer::IImGuiRenderer& imgui_renderer() const;
        // Setters modules
        template<typename T> requires std::is_base_of_v<IModule, T>
        void set_module(std::unique_ptr<T> module = std::make_unique<T>());
        void set_window(std::unique_ptr<window::IMainWindow> window);
        void set_event_manager(std::unique_ptr<event::IEventManager> event_manager);
        void set_engine(std::unique_ptr<engine::IEngine> engine);
        void set_renderer(std::unique_ptr<renderer::IRenderer> renderer);
        void set_imgui_renderer(std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer);
        // Helpers
        /*!
         * Vérifie si tous les modules sont bien valide.
         * @param create_missing Si true, crée les module invalide par default.
         * @return false si au moins un module n'était pas valide
         */
        bool check_modules(bool create_missing = true);
        bool set_modules();
        void initialise();
        void configure();
        void update();
        void cleanup();
        void on_quit();

    private:
        // Modules
        std::unique_ptr<window::IMainWindow> m_window;
        std::unique_ptr<event::IEventManager> m_event_manager;
        std::unique_ptr<engine::IEngine> m_engine;
        std::unique_ptr<renderer::IRenderer> m_renderer;
        std::unique_ptr<renderer::IImGuiRenderer> m_imgui_renderer;
        // Utils
        std::shared_ptr<spdlog::logger> m_logger;
    public:
        // Désactiver la copie
        ModuleSet(const ModuleSet&) = delete;
        ModuleSet& operator=(const ModuleSet&) = delete;
        // Activer le déplacement
        ModuleSet(ModuleSet&& other) noexcept;
        ModuleSet& operator=(ModuleSet&& other) noexcept;
    };

}
#include "module_set.inl"
#endif // BINTJEKIT_CORE_MODULE_SET_HPP
