/*!
 * @author bintjeman
 * @date 17.07.25
 * @name module_set.inl
 */
#ifndef BINTJEKIT_CORE_MODULE_SET_INL
#define BINTJEKIT_CORE_MODULE_SET_INL
#pragma once
#include <spdlog/spdlog.h>
namespace bnjkit::core {
    template<typename T> requires std::is_base_of_v<IModule, T>
    T& ModuleSet::get() {
        if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
            return * static_cast<T*>(m_window.get());
        } else if constexpr (std::is_base_of_v<renderer::IRenderer, T>) {
            return * static_cast<T*>(m_renderer.get());
        } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
            return * static_cast<T*>(m_engine.get());
        } else if constexpr (std::is_base_of_v<imgui::IImGuiRenderer, T>) {
            return * static_cast<T*>(m_imgui_renderer.get());
        }else if constexpr (std::is_base_of_v<event::IEventManager, T>) {
            return * static_cast<T*>(m_event_manager.get());
        }
        m_logger->error("Module {} not found", typeid(T).name());
        return nullptr;
    }

    template<typename T> requires std::is_base_of_v<IModule, T>
    const T& ModuleSet::get() const {
        if constexpr (std::is_base_of_v<window::IMainWindow, T>) {
            return window();
        } else if constexpr (std::is_base_of_v<renderer::IRenderer, T>) {
            return renderer();
        } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
            return engine();
        } else if constexpr (std::is_base_of_v<imgui::IImGuiRenderer, T>) {
            return imgui_renderer();
        }else if constexpr (std::is_base_of_v<event::IEventManager, T>) {
            return event_manager();
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
        } else if constexpr (std::is_base_of_v<engine::IEngine, T>) {
            set_engine(std::move(module));
        } else if constexpr (std::is_base_of_v<imgui::IImGuiRenderer, T>) {
            set_imgui_renderer(std::move(module));
        }else if constexpr (std::is_base_of_v<event::IEventManager, T>) {
            set_event_manager(std::move(module));
        }
    }
}
#endif // BINTJEKIT_CORE_MODULE_SET_INL
