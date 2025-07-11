/*!
 * @author bintjeman
 * @date 26.06.25
 * @name imguirenderer.hpp
 */

#ifndef EVO_IMGUIRENDERER_HPP
#define EVO_IMGUIRENDERER_HPP
#pragma once
#include <bintjekit/renderer/i_bnjkit_imgui.hpp>
namespace bnjkit::event {
    class ICoreEventHandler;
}

namespace evo {
    namespace engine {
        class EvobotEngine;
    } // engine
    namespace event {
        class EventManager;
    }
        namespace renderer {
        class ImGuiRenderer final : public bnjkit::renderer::IImGuiRenderer {
        public:
            ImGuiRenderer();
            ~ImGuiRenderer() override;
            void draw() override;
            void configure() override;
            void on_quit() override;
            void set_engine(bnjkit::engine::IEngine* engine) override;
            void set_core_event_handler(bnjkit::event::ICoreEventHandler* core_event_handler) override;
        private:
            event::EventManager* m_event_manager;
            const engine::EvobotEngine* m_evobot_engine;
            bool m_draw_info_window{true};
            bool m_draw_debug_window{false};
            bool m_draw_evobot_window{true};
            bool m_draw_controls_window{false};
            bool m_draw_menu{true};
        };
    } // renderer
} // evo

#endif //EVO_IMGUIRENDERER_HPP
