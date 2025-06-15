/*!
 * @author bintjeman
 * @date 15.06.25
 * @name imgui.hpp
 */
#ifndef BNJKIT_IMGUI_HPP
#define BNJKIT_IMGUI_HPP
#pragma once
#include <memory>

#include "spdlog/fwd.h"

namespace sf {
    class Event;
    class RenderWindow;
}

namespace bnjkit {
    namespace renderer {
        class IImGuiRenderer {
        public:
            IImGuiRenderer();
            virtual ~IImGuiRenderer();
            virtual void init();
            virtual void update();
            virtual void process_events(sf::Event &event);
            virtual void draw();
            void render();
            void set_window(sf::RenderWindow *window);
            static void shutdown();

        protected:
            std::shared_ptr<spdlog::logger> m_logger;

        private:
            sf::RenderWindow *m_window = nullptr;

        public:
            IImGuiRenderer(const IImGuiRenderer &) = delete;
            IImGuiRenderer &operator=(const IImGuiRenderer &) = delete;
        };
    } // renderer
} // bnjkit
#endif // BNJKIT_IMGUI_HPP
