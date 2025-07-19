/*!
 * @author bintjeman
 * @date 19.07.25
 * @name im_gui_renderer.hpp
 */

#ifndef IM_GUI_RENDERER_HPP
#define IM_GUI_RENDERER_HPP
#pragma once
#include <bintjekit/renderer/i_imgui_renderer.hpp>

namespace bil {
    class ImGuiRenderer : public bnjkit::renderer::IImGuiRenderer {
    public:
        ImGuiRenderer();
        ~ImGuiRenderer() override;
        void configure() override;
        void process_events(const sf::Event& event) override;
        void draw() override;
        [[nodiscard]] std::string name() const override;

    private:
        bool m_show_debug_window = true;
        bool m_show_billard_window = true;
        bool m_show_controls_window = true;
        bool m_show_menu = true;
#ifndef NDEBUG
        bool m_show_demo_window = false;
#endif
    };
} // bil

#endif //IM_GUI_RENDERER_HPP
