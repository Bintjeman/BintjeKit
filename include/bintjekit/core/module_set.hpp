/*!
 * @author bintjeman
 * @date 16.07.25
 * @name module_set.hpp
 */
#ifndef BINTJEKIT_CORE_MODULE_SET_HPP
#define BINTJEKIT_CORE_MODULE_SET_HPP
#pragma once
#include <memory>
// #include <spdlog/fwd.h>
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/logger.hpp"

namespace bnjkit {
    namespace window {
        class IMainWindow;
    }

    namespace renderer {
        class IRenderer;
        class IImGuiRenderer;
    }

    namespace event {
        class ICoreEventHandler;
    }

    namespace engine {
        class IEngine;
    }
}

namespace bnjkit::core {
    class ModuleSet {
    public:
        ModuleSet();
        ~ModuleSet();
        // Getters modules
        template<typename T> requires std::is_base_of_v<IModule, T>
        T& get();
        template<typename T> requires std::is_base_of_v<IModule, T>
        const T& get() const;
        window::IMainWindow& window();
        renderer::IRenderer& renderer();
        event::ICoreEventHandler& core_event_handler();
        engine::IEngine& engine();
        renderer::IImGuiRenderer& imgui_renderer();
        [[nodiscard]] window::IMainWindow& window() const;
        [[nodiscard]] renderer::IRenderer& renderer() const;
        [[nodiscard]] event::ICoreEventHandler& core_event_handler() const;
        [[nodiscard]] engine::IEngine& engine() const;
        [[nodiscard]] renderer::IImGuiRenderer& imgui_renderer() const;

        // Setters modules
        template<typename T> requires std::is_base_of_v<IModule, T>
        void set_module(std::unique_ptr<T> module = std::make_unique<T>());
        void set_window(std::unique_ptr<window::IMainWindow> window);
        void set_renderer(std::unique_ptr<renderer::IRenderer> renderer);
        void set_core_event_handler(std::unique_ptr<event::ICoreEventHandler> core_event_handler);
        void set_world(std::unique_ptr<engine::IEngine> world);
        void set_imgui_renderer(std::unique_ptr<renderer::IImGuiRenderer> imgui_renderer);
        // Helpers
        bool check_modules(bool create_missing = true);
        void initialise();
        void configure();
        void update();
        void cleanup();
        void on_quit();

    private:
        // Modules
        std::unique_ptr<window::IMainWindow> m_window;
        std::unique_ptr<renderer::IRenderer> m_renderer;
        std::unique_ptr<event::ICoreEventHandler> m_core_event_handler;
        std::unique_ptr<engine::IEngine> m_engine;
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
