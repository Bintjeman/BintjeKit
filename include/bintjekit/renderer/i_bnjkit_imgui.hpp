/*!
 * @author bintjeman
 * @date 15.06.25
 * @name imgui.hpp
 */
#ifndef BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
#define BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
#pragma once
#include <memory>
#include "spdlog/fwd.h"

namespace sf {
    class Event;
    class RenderWindow;
}

namespace bnjkit {
    namespace engine {
        class IEngine;
    };
    namespace core {
        class Core;
    };
    namespace renderer {
        class IImGuiRenderer {
            class ImGuiContext {
            public:
                explicit ImGuiContext(sf::RenderWindow *window);
                ~ImGuiContext();
            };

        public:
            IImGuiRenderer();
            virtual ~IImGuiRenderer();
            virtual void init();
            virtual void update();
            virtual void process_events(sf::Event &event);
            virtual void draw();
            void render();
            void set_window(sf::RenderWindow *window);
            virtual void set_engine(engine::IEngine *engine);
            virtual void set_core(core::Core *core);
            void shutdown();

        protected:
            std::shared_ptr<spdlog::logger> m_logger;
            engine::IEngine *m_engine;
            core::Core *m_core;
        private:
            std::unique_ptr<ImGuiContext> m_context;
            sf::RenderWindow *m_window = nullptr;

        public:
            IImGuiRenderer(const IImGuiRenderer &) = delete;
            IImGuiRenderer &operator=(const IImGuiRenderer &) = delete;
        };
    } // renderer
} // bnjkit
#endif // BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
