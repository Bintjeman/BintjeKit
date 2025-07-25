/*!
 * @author bintjeman
 * @date 23.07.25
 * @name im_gui_renderer.hpp
 */

#ifndef EVO_RENDERER_IMGUI_RENDERER_HPP
#define EVO_RENDERER_IMGUI_RENDERER_HPP
#pragma once
#include <bintjekit/imgui/i_imgui_renderer.hpp>

namespace evo::imgui {
    class ImGuiRenderer final : public bnjkit::imgui::IImGuiRenderer {
    public:
        static bool has_focus();

        ImGuiRenderer();
        ~ImGuiRenderer() override;
        void configure() override;
        void draw() override;
        [[nodiscard]] std::string name() const override;
        void on_quit() override;

    private:
        bool m_show_demo_window = false;
        bool m_show_menu = true;
        bool m_show_settings_window = true;
    };
}
#endif
