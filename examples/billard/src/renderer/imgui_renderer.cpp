/*!
 * @author bintjeman
 * @date 19.07.25
 * @name im_gui_renderer.cpp
 */

#include "imgui_renderer.hpp"

#include <spdlog/spdlog.h>
#include <imgui.h>

#include "bintjekit/core/module_set.hpp"
#include "engine/billard.hpp"
#include "engine/components/entity.hpp"

namespace bil {
    ImGuiRenderer::ImGuiRenderer() {
        m_logger->info("ImGuiRenderer created");
    }
    ImGuiRenderer::~ImGuiRenderer() {
        m_logger->info("ImGuiRenderer destroyed");
    }
    void ImGuiRenderer::configure() {
        IImGuiRenderer::configure();
        m_show_menu = m_settings.get_or_set("/Showing/Menu", true);
        m_show_debug_window = m_settings.get_or_set("/Showing/Debug window", true);
        m_show_billard_window = m_settings.get_or_set("/Showing/Billard window", true);
        m_show_controls_window = m_settings.get_or_set("/Showing/Controls window", true);
    }
    void ImGuiRenderer::process_events(const sf::Event& event) {
        IImGuiRenderer::process_events(event);
    }
    void ImGuiRenderer::draw() {
        IImGuiRenderer::draw();
        static auto& engine = m_modules->engine();
        static auto& billard = dynamic_cast<bil::Billard&>(engine);
        if (m_show_menu) {
            ImGui::BeginMainMenuBar();
            if (ImGui::BeginMenu("File")) {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("Debug window", nullptr, & m_show_debug_window);
                ImGui::MenuItem("Billard window", nullptr, & m_show_billard_window);
                ImGui::MenuItem("Controls window", nullptr, & m_show_controls_window);
                ImGui::EndMenu();
            }
#ifndef NDEBUG
            if (ImGui::BeginMenu("#DEBUG")) {
                ImGui::MenuItem("Demo window", nullptr, & m_show_demo_window);
                ImGui::EndMenu();
            }
#endif
            ImGui::EndMainMenuBar();
        }
#ifndef NDEBUG
        if (m_show_demo_window) {
            ImGui::ShowDemoWindow(& m_show_demo_window);
        }
#endif
        if (m_show_billard_window) {
            ImGui::Begin("Billard", & m_show_billard_window);
            auto ball_view = billard.registry().view<components::BallFlag>();
            std::size_t ball_count = ball_view.size();
            ImGui::Text("Balls: %lu", ball_count);
            ImGui::End();
        }
        if (m_show_controls_window) {
            ImGui::Begin("Controls", & m_show_controls_window);
            if (ImGui::CollapsingHeader("Loggers")) {
                static const char* level_enum[] = {
                    spdlog::level::to_string_view(spdlog::level::trace).data(),
                    spdlog::level::to_string_view(spdlog::level::debug).data(),
                    spdlog::level::to_string_view(spdlog::level::info).data(),
                    spdlog::level::to_string_view(spdlog::level::warn).data(),
                    spdlog::level::to_string_view(spdlog::level::err).data(),
                    spdlog::level::to_string_view(spdlog::level::critical).data()
                };
                static constexpr auto logger_enum = std::array<std::string, 10>{
                    bnjkit::literals::logger::APP,
                    bnjkit::literals::logger::ENGINE,
                    bnjkit::literals::logger::RENDERER,
                    bnjkit::literals::logger::WINDOW,
                    bnjkit::literals::logger::EVENT,
                    bnjkit::literals::logger::ENTITY,
                    bnjkit::literals::logger::CONFIGURATION,
                    bnjkit::literals::logger::CONFIGURATION,
                    bnjkit::literals::logger::ECS,
                    bnjkit::literals::logger::LOG
                };
                for (auto& logger_name: logger_enum) {
                    auto logger = bnjkit::logger::Logger::get_logger(logger_name);
                    int level = logger->level();
                    if (ImGui::Combo(logger_name.c_str(), &level, level_enum, IM_ARRAYSIZE(level_enum))) {
                        logger->set_level(static_cast<spdlog::level::level_enum>(level));
                    }
                }
            }
            ImGui::End();
        }
    }
    std::string ImGuiRenderer::name() const {
        return "Billard ImGui Renderer";
    }
} // bil
