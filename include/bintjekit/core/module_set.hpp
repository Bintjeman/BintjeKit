/*!
 * @author bintjeman
 * @date 16.07.25
 * @name module_set.hpp
 */
#ifndef BINTJEKIT_CORE_MODULE_SET_HPP
#define BINTJEKIT_CORE_MODULE_SET_HPP
#pragma once
#include <memory>
#include <spdlog/fwd.h>
#include "bintjekit/core/i_module.hpp"

namespace bnjkit {
    namespace window {
        class IMainWindow;
    }

    namespace renderer {
        class IRenderer;
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
        window::IMainWindow& get_window();
        renderer::IRenderer& get_renderer();
        event::ICoreEventHandler& get_core_event_handler();
        engine::IEngine& get_engine();
        [[nodiscard]] window::IMainWindow& get_window() const;
        [[nodiscard]] renderer::IRenderer& get_renderer() const;
        [[nodiscard]] event::ICoreEventHandler& get_core_event_handler() const;
        [[nodiscard]] engine::IEngine& get_engine() const;
        // Setters modules
        template<typename T>
            requires std::is_base_of_v<IModule, T>
        void set_module();
        void set_window(std::unique_ptr<window::IMainWindow> window);
        void set_renderer(std::unique_ptr<renderer::IRenderer> renderer);
        void set_core_event_handler(std::unique_ptr<event::ICoreEventHandler> core_event_handler);
        void set_engine(std::unique_ptr<engine::IEngine> world);
        // Helpers
        bool check_modules(bool create_missing = true);
        void initialise();
        void configure();
        void update();
        void cleanup();
        void on_quit();

    private:
        std::unique_ptr<window::IMainWindow> m_window;
        std::unique_ptr<renderer::IRenderer> m_renderer;
        std::unique_ptr<event::ICoreEventHandler> m_core_event_handler;
        std::unique_ptr<engine::IEngine> m_engine;
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
    void ModuleSet::set_module() {
        if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
            set_window(std::make_unique<T>());
        } else if constexpr (std::is_base_of_v<renderer::IRenderer, T>) {
            set_renderer(std::make_unique<T>());
        } else if constexpr (std::is_base_of_v<event::ICoreEventHandler, T>) {
            set_core_event_handler(std::make_unique<T>());
        } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
            set_engine(std::make_unique<T>());
        }
    }
}
#endif // BINTJEKIT_CORE_MODULE_SET_HPP
