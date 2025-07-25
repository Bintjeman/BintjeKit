/*!
 * @author bintjeman
 * @date 23.07.25
 * @name im_gui_renderer.cpp
 */
#include "imgui/imgui_renderer.hpp"
#include <imgui.h>
#include <bintjekit/core/common.hpp>
#include <bintjekit/logger/logger.hpp>
#include <spdlog/spdlog.h>

namespace evo::imgui {
    namespace {
        constexpr auto DEMO_JSON_PTR = "/Showing/Demo window";
        constexpr auto MENU_JSON_PTR = "/Showing/Menu";
        constexpr auto SETTINGS_JSON_PTR = "/Showing/Settings window";
    }

    ImGuiRenderer::ImGuiRenderer() {
        m_logger->info("Build {}", name());
    }
    ImGuiRenderer::~ImGuiRenderer() {
        m_logger->info("Destroy {}", name());
    }
    void ImGuiRenderer::configure() {
        m_logger->trace("Configure {}", name());
        m_show_demo_window = m_settings.get_or_set(DEMO_JSON_PTR, m_show_demo_window);
        m_show_menu = m_settings.get_or_set(MENU_JSON_PTR, m_show_menu);
        m_show_settings_window = m_settings.get_or_set(SETTINGS_JSON_PTR, m_show_settings_window);
    }
    void ImGuiRenderer::draw() {
        if (m_show_menu) {
            ImGui::BeginMainMenuBar();
            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("Demo window", nullptr, & m_show_demo_window);
                ImGui::MenuItem("Settings window", nullptr, & m_show_settings_window);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        if (m_show_settings_window) {
            if (ImGui::Begin("Settings", & m_show_settings_window)) {
                if (ImGui::CollapsingHeader("Loggers")) {
                    for (auto& logger_name: bnjkit::literals::logger_enum) {
                        const auto logger = bnjkit::logger::Logger::get_logger(logger_name);
                        int level = logger->level();
                        if (ImGui::Combo(logger_name.c_str(), & level, bnjkit::logger::LEVEL_ENUM,
                                         IM_ARRAYSIZE(bnjkit::logger::LEVEL_ENUM))) {
                            m_logger->info("Setting level of {} to {}", logger_name, level);
                            logger->set_level(static_cast<spdlog::level::level_enum>(level));
                        }
                    }
                }
                ImGui::End();
            }
        }
        if (m_show_demo_window) {
            ImGui::ShowDemoWindow(& m_show_demo_window);
        }
    }
    bool ImGuiRenderer::has_focus() {
        return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
    }
    std::string ImGuiRenderer::name() const {
        return "Evo ImGui Renderer";
    }
    void ImGuiRenderer::on_quit() {
        m_logger->info("Update settings");
        m_settings.set(DEMO_JSON_PTR, m_show_demo_window);
        m_settings.set(MENU_JSON_PTR, m_show_menu);
        m_settings.set(SETTINGS_JSON_PTR, m_show_settings_window);
    }
}
