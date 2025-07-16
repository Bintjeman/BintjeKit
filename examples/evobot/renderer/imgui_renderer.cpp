/*!
 * @author bintjeman
 * @date 26.06.25
 * @name imguirenderer.cpp
 */
#include "imgui_renderer.hpp"
#include <imgui.h>
#include <spdlog/logger.h>
#include <bintjekit/logger.hpp>
#include <bintjekit/core/core.hpp>
#include <bintjekit/engine/i_engine.hpp>
#include "application/event_manager.hpp"
#include "evobot_engine/evobot_engine.hpp"
#include "evobot_engine/evo_world.hpp"
#include "evobot_engine/components/base_components.hpp"
namespace evo::renderer {
    ImGuiRenderer::ImGuiRenderer(): m_event_manager(nullptr), m_evobot_engine(nullptr) {
        m_logger->info("ImGuiRenderer: created");
    }
    ImGuiRenderer::~ImGuiRenderer() {
        m_logger->info("ImGuiRenderer: destroyed");
    }
    void ImGuiRenderer::draw() {
        if (m_draw_menu) {
            ImGui::BeginMainMenuBar();
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Draw evobot window", nullptr, & m_draw_evobot_window)) {}
                if (ImGui::MenuItem("Draw info window", nullptr, & m_draw_info_window)) {}
                if (ImGui::MenuItem("Draw debug window", nullptr, & m_draw_debug_window)) {}
                if (ImGui::MenuItem("Draw controls window", nullptr,
                                    & m_draw_controls_window)) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (m_draw_evobot_window) {
            ImGui::Begin("Evobot", & m_draw_evobot_window);
            if (auto world = m_evobot_engine->world()) {
                auto evobot_view = world->registry().view<engine::comp::EvobotTag>();
                auto glob_view = world->registry().view<engine::comp::GlobTag>();
                std::size_t evobot_count = evobot_view.size();
                std::size_t glob_count = glob_view.size();
                std::size_t total_count = evobot_count + glob_count;
                ImGui::Text("Total entities count: %zu", total_count);
                ImGui::Text("Evobot count: %zu", evobot_count);
                ImGui::Text("Glob count: %zu", glob_count);

            }
            ImGui::End();
        }
        if (m_draw_info_window) {
            ImGui::Begin("Info", & m_draw_info_window);
            if (ImGui::CollapsingHeader("Loggers")) {
                static const char* items[] = {
                    "Trace", "Debug", "Info", "Warning", "Error", "Critical", "Off"
                };
                static const char* enum_module[] = {
                    // bnjkit::core::module_names::NONE,
                    bnjkit::literals::logger::APP,
                    bnjkit::literals::logger::LOG,
                    bnjkit::literals::logger::CORE,
                    bnjkit::literals::logger::ENGINE,
                    bnjkit::literals::logger::RENDERER,
                    bnjkit::literals::logger::WINDOW,
                    bnjkit::literals::logger::EVENT,
                    bnjkit::literals::logger::CONFIGURATION,
                };
                for (const auto& module: enum_module) {
                    std::string title = std::string(module) + " logger level";
                    int current_level = bnjkit::core::Logger::get_logger(module)->level();
                    if (ImGui::Combo(title.c_str(), & current_level, items,
                                     IM_ARRAYSIZE(items))) {
                        const auto int_to_level = [](const int level) {
                            switch (level) {
                                case 0: return spdlog::level::trace;
                                case 1: return spdlog::level::debug;
                                case 2: return spdlog::level::info;
                                case 3: return spdlog::level::warn;
                                case 4: return spdlog::level::err;
                                case 5: return spdlog::level::critical;
                                default: return spdlog::level::off;
                            }
                        };
                        m_logger->trace("{} logger level changed to {}", module,
                                        items[current_level]);
                        bnjkit::core::Logger::get_logger(
                            module)->set_level(
                            int_to_level(current_level));
                    }
                }
            }
            ImGui::End();
        }
        if (m_draw_debug_window) {
            ImGui::Begin("Debug", & m_draw_debug_window);
            ImGui::Text("FPS: %f", static_cast<double>(ImGui::GetIO().Framerate));
            auto window_ps = m_core->window_frequency();
            auto window_effective_ps = m_core->window_effective_frequency();
            auto renderer_ps = m_core->renderer_frequency();
            auto renderer_effective_ps = m_core->renderer_effective_frequency();
            auto engine_ps = m_core->engine_frequency();
            auto engine_effective_ps = m_core->engine_effective_frequency();
            ImGui::Text("Window: %ld\t(%ld)", window_effective_ps, window_ps);
            ImGui::Text("Renderer: %ld\t(%ld)", renderer_effective_ps, renderer_ps);
            ImGui::Text("Engine: %ld\t(%ld)", engine_effective_ps, engine_ps);
            ImGui::End();
        }
        if (m_draw_controls_window) {
            if (ImGui::Begin("Controls", & m_draw_controls_window)) {
                auto state = m_core->state();
                ImGui::Text("Core state: %s",
                            bnjkit::core::Core::state_to_string(state).c_str());
            }
            if (ImGui::Button("Run")) {
                m_event_manager->run_button();
            }
            ImGui::SameLine();
            if (ImGui::Button("Pause")) {
                m_event_manager->pause_button();
            }
            ImGui::SameLine();
            if (ImGui::Button("Stop")) {
                m_event_manager->stop_button();
            }
            ImGui::End();
        }
    }
    void ImGuiRenderer::configure() {
        m_logger->info("ImGuiRenderer: configuring");
        m_draw_menu = m_settings.get_or_set("/View/Draw menu", true);
        m_draw_info_window = m_settings.get_or_set("/View/Draw info window", true);
        m_draw_debug_window = m_settings.get_or_set("/View/Draw debug window", true);
        m_draw_evobot_window = m_settings.get_or_set("/View/Draw evobot window", true);
        m_draw_controls_window = m_settings.get_or_set("/View/Draw controls window", true);
    }
    void ImGuiRenderer::on_quit() {
        m_logger->info("ImGuiRenderer: on quit");
        m_settings.set("/View/Draw menu", m_draw_menu);
        m_settings.set("/View/Draw info window", m_draw_info_window);
        m_settings.set("/View/Draw debug window", m_draw_debug_window);
        m_settings.set("/View/Draw evobot window", m_draw_evobot_window);
        m_settings.set("/View/Draw controls window", m_draw_controls_window);
    }
    void ImGuiRenderer::set_engine(bnjkit::ecs::IEngine* engine) {
        IImGuiRenderer::set_engine(engine);
        m_evobot_engine = dynamic_cast<engine::EvobotEngine*>(engine);
    }
    void ImGuiRenderer::set_core_event_handler(
        bnjkit::event::ICoreEventHandler* core_event_handler) {
        IImGuiRenderer::set_core_event_handler(core_event_handler);
        m_event_manager = dynamic_cast<event::EventManager*>(core_event_handler);
    }
} // renderer
// evo
