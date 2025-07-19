/*!
 * @author bintjeman
 * @date 18.07.25
 * @name im_gui_renderer.hpp
 */

#ifndef IM_GUI_RENDERER_HPP
#define IM_GUI_RENDERER_HPP
#pragma once
#include <bintjekit/renderer/i_imgui_renderer.hpp>

namespace utypes {
    class ImGuiRenderer : public bnjkit::renderer::IImGuiRenderer {
        public:
            ImGuiRenderer();
            ~ImGuiRenderer();
    };
} // utypes

#endif //IM_GUI_RENDERER_HPP
