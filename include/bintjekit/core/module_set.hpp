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
        window::IMainWindow& get_window();
        renderer::IRenderer& get_renderer();
        event::ICoreEventHandler& get_core_event_handler();
        engine::IEngine& get_engine();
        renderer::IImGuiRenderer& get_imgui_renderer();
        [[nodiscard]] window::IMainWindow& get_window() const;
        [[nodiscard]] renderer::IRenderer& get_renderer() const;
        [[nodiscard]] event::ICoreEventHandler& get_core_event_handler() const;
        [[nodiscard]] engine::IEngine& get_engine() const;
        [[nodiscard]] renderer::IImGuiRenderer& get_imgui_renderer() const;

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

    template<typename T> requires std::is_base_of_v<IModule, T>
    T& ModuleSet::get() {
        if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
            return *static_cast<T*>(m_window.get());
        } else if constexpr (std::is_base_of_v<renderer::IRenderer, T>) {
            return *static_cast<T*>(m_renderer.get());
        } else if constexpr (std::is_base_of_v<event::ICoreEventHandler, T>) {
            return *static_cast<T*>(m_core_event_handler.get());
        } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
            return *static_cast<T*>(m_engine.get());
        } else if constexpr (std::is_base_of_v<renderer::IImGuiRenderer, T>) {
            return *static_cast<T*>(m_imgui_renderer.get());
        }
        m_logger->error("Module {} not found", typeid(T).name());
        return nullptr;
    }

    template<typename T> requires std::is_base_of_v<IModule, T>
    const T& ModuleSet::get() const {
        if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
            return get_window();
        } else if constexpr (std::is_base_of_v<renderer::IRenderer, T>) {
            return get_renderer();
        } else if constexpr (std::is_base_of_v<event::ICoreEventHandler, T>) {
            return get_core_event_handler();
        } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
            return get_engine();
        } else if constexpr (std::is_base_of_v<renderer::IImGuiRenderer, T>) {
            return get_imgui_renderer();
        }
        m_logger->error("Module {} not found", typeid(T).name());
        return nullptr;
    }

    template<typename T> requires std::is_base_of_v<IModule, T>
    void ModuleSet::set_module(std::unique_ptr<T> module) {
        if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
            set_window(std::move(module));
        } else if constexpr (std::is_base_of_v<renderer::IRenderer, T>) {
            set_renderer(std::move(module));
        } else if constexpr (std::is_base_of_v<event::ICoreEventHandler, T>) {
            set_core_event_handler(std::move(module));
        } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
            set_world(std::move(module));
        } else if constexpr (std::is_base_of_v<renderer::IImGuiRenderer, T>) {
            set_imgui_renderer(std::move(module));
        }
    }
}
#endif // BINTJEKIT_CORE_MODULE_SET_HPP
