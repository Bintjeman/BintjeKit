/*!
 * @author bintjeman
 * @date 15.06.25
 * @name imgui.hpp
 */
#ifndef BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
#define BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
#pragma once
#include <memory>
#include <oneapi/tbb/profiling.h>
#include <spdlog/fwd.h>

#include "bintjekit/core/i_module.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"

namespace sf {
    class Event;
    class RenderWindow;
}

namespace bnjkit {
    namespace engine {
        class IEngine;
    }

    namespace core {
        class Core;
    }

    namespace event {
        class ICoreEventHandler;
    }

    namespace renderer {
        class IRenderer;
        class IImGuiRenderer : public core::IModule, event::IEventListener {
            class ImGuiContext {
            public:
                explicit ImGuiContext(sf::RenderWindow* window);
                ~ImGuiContext();
            };

        public:
            IImGuiRenderer();
            ~IImGuiRenderer() override;
            virtual void init();
            virtual void update();
            virtual void process_events(sf::Event& event);
            virtual void draw();
            void render() const;
            void set_window(sf::RenderWindow* window);
            virtual void set_engine(engine::IEngine* engine);
            virtual void set_core(core::Core* core);
            virtual void set_core_event_handler(event::ICoreEventHandler* core_event_handler);
            virtual void set_renderer(IRenderer* renderer);
            static void shutdown();
            [[nodiscard]] std::string name() const override;

        protected:
            std::shared_ptr<spdlog::logger> m_logger;
            engine::IEngine* m_engine;
            core::Core* m_core;
            event::ICoreEventHandler* m_core_event_handler;
            IRenderer* m_renderer;

        private:
            std::unique_ptr<ImGuiContext> m_context;
            sf::RenderWindow* m_window = nullptr;

        public:
            IImGuiRenderer(const IImGuiRenderer&) = delete;
            IImGuiRenderer& operator=(const IImGuiRenderer&) = delete;
        };
    } // renderer
} // bnjkit
#endif // BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
